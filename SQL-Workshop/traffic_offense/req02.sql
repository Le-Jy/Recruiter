SELECT * FROM public.traffic_violations
WHERE license_plate LIKE 'AZ__36_'
AND violation_date <= TIMESTAMP '2059-12-3 21:00' + INTERVAL '1' hour
AND violation_date >= TIMESTAMP '2059-12-3 21:00' - INTERVAL '1' hour
