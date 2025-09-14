(SELECT
    person_id,
    validation,
    created_at
FROM transport.metro_usage_logs
WHERE created_at BETWEEN timestamp '2059-12-03 20:00' AND
                    timestamp '2059-12-03 22:00'
ORDER BY created_at ASC
LIMIT 10)
UNION
SELECT
    person_id,
    validation,
    created_at
FROM transport.metro_usage_logs
WHERE created_at BETWEEN timestamp '2059-12-03 12:00' AND
                        timestamp '2059-12-03 14:00'
ORDER BY created_at DESC
