package com.epita.ssse.restServer.service;

import com.epita.ssse.restServer.model.TelematicsData;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import java.text.SimpleDateFormat;
import java.util.Date;

@Service
public class TelematicsService {
    private static final Logger logger =
            LoggerFactory.getLogger(TelematicsService.class);

    public void logInfo(TelematicsData data) {
        SimpleDateFormat formatter = new SimpleDateFormat("yy:MM:dd HH:mm:ss");
        String formattedDate = formatter.format(new Date(data.getLocalTime() * 1000));
        logger.info("VIN: {}, Date: {}, Passagers: {}",
                data.getVehicleId(), formattedDate, data.getPassengerNumber());
    }
}
