SELECT * FROM public.traffic_violations
WHERE license_plate LIKE 'AZ__36_'
AND (description = 'SPEED_AND_TRAFFIC_VIOLATION'
OR description = 'RECKLESS_AND_DANGEROUS_DRIVING')
AND violation_date <= TIMESTAMP '2059-12-3 21:00' + INTERVAL '1' hour
AND violation_date >= TIMESTAMP '2059-12-3 21:00' - INTERVAL '1' hour
