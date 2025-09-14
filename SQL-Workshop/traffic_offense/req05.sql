SELECT tv.id, tv.description, tv.violation_date, tv.street_id, tv.license_plate
FROM (SELECT * FROM public.traffic_violations
    WHERE license_plate LIKE 'AZ__36_'
    AND (description = 'SPEED_AND_TRAFFIC_VIOLATION'
        OR description = 'RECKLESS_AND_DANGEROUS_DRIVING')
    AND violation_date <= TIMESTAMP '2059-12-3 21:00' + INTERVAL '1' hour
    AND violation_date >= TIMESTAMP '2059-12-3 21:00' - INTERVAL '1' hour) AS sus, public.traffic_violations AS tv
WHERE sus.license_plate = tv.license_plate
AND tv.violation_date < TIMESTAMP '2059-12-03 12:00' + INTERVAL '12' hour
AND tv.violation_date >= TIMESTAMP '2059-12-03 12:00' - INTERVAL '12' hour
