package fr.epita.assistants.travel;

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.Temporal;
import java.time.temporal.TemporalAmount;

public class Travel {
    public static void travelTo(Country source, Country destination) {
        StringBuilder boarding = new StringBuilder("Boarding in ");
        ZoneId zoneId = ZoneId.of(source.countryZone);
        LocalDateTime localDateTime = LocalDateTime.now();
        ZonedDateTime zonedDateTime = localDateTime.atZone(zoneId);
        DateTimeFormatter formatter = DateTimeFormatter.RFC_1123_DATE_TIME;
        boarding.append(source.countryName).append(", local date and time is: ").append(formatter.format(zonedDateTime));
        System.out.println(boarding);
        StringBuilder landing = new StringBuilder("Landing in ");
        ZoneId landingzoneId = ZoneId.of(destination.countryZone);
        LocalDateTime landinglocalDateTime = LocalDateTime.now().plusHours(source.travelTimes.get(destination.countryName));
        ZonedDateTime landingzonedDateTime = landinglocalDateTime.atZone(landingzoneId);
        landing.append(destination.countryName).append(", local date and time on arrival will be: ").append(formatter.format(landingzonedDateTime));
        System.out.println(landing);
    }
}
