package com.epita.ssse.restServer.model;

import lombok.*;

@Getter
@Setter
@ToString
@NoArgsConstructor
@AllArgsConstructor
public class TelematicsData {
    private String vehicleId;
    private Long localTime;
    private Integer passengerNumber;
}
