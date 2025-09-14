SELECT
    P.id,
    P.first_name,
    P.last_name
FROM
    public.people AS P,
    transport.metro_usage_logs AS MUL
WHERE EXISTS
   (
        SELECT
            id
        FROM transport.metro_stations
        WHERE name = 'Morgane Abeille' AND
        MUL.station_id = id AND
        P.id = MUL.person_id
    )
