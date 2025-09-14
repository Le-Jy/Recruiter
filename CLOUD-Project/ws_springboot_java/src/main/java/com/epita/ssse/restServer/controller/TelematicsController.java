package com.epita.ssse.restServer.controller;

import com.epita.ssse.restServer.model.TelematicsData;
import com.epita.ssse.restServer.service.TelematicsService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/ssie/tcs")
public class TelematicsController {
    private static final Logger logger =
            LoggerFactory.getLogger(TelematicsController.class);
    private final TelematicsService telematicsService;

    // Constructor injection
    public TelematicsController(TelematicsService telematicsService) {
        this.telematicsService = telematicsService;
    }
    @PostMapping("/veh")
    public ResponseEntity<Void> receiveData(@RequestBody TelematicsData data) {
        if (data.getPassengerNumber() == null || data.getVehicleId() == null || data.getVehicleId().isEmpty() || data.getPassengerNumber() < 0 || data.getLocalTime() == null) {
            logger.error("Invalid data received: {}", data);
            return ResponseEntity.badRequest().build();
        }
        telematicsService.logInfo(data);

        return ResponseEntity.ok().build();
    }
}
