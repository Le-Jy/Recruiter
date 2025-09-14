SELECT
    ppl.id AS person_id,
    ppl.first_name AS person_first_name,
    ppl.last_name AS person_last_name,
    SEL.created_at,
    'shop' AS place,
    SEL.shop_id AS place_id
FROM public.shop_entrance_logs AS SEL, public.people AS ppl
WHERE   ppl.id = SEL.person_id AND
        SEL.created_at BETWEEN timestamp '2059-12-03 17:00' AND
        timestamp '2059-12-03 22:00'
UNION
SELECT
    ppl.id AS person_id,
    ppl.first_name AS person_first_name,
    ppl.last_name AS person_last_name,
    SL.created_at,
    'street' AS place,
    SL.street_id AS place_id
FROM public.street_logs AS SL, public.people AS ppl
WHERE   ppl.id = SL.person_id AND
        SL.created_at BETWEEN timestamp '2059-12-03 17:00' AND
        timestamp '2059-12-03 22:00'
UNION
SELECT
    ppl.id AS person_id,
    ppl.first_name AS person_first_name,
    ppl.last_name AS person_last_name,
    MUL.created_at,
    'metro' AS place,
    MUL.station_id AS place_id
FROM transport.metro_usage_logs AS MUL, public.people AS ppl
WHERE   ppl.id = MUL.person_id AND
        MUL.created_at BETWEEN timestamp '2059-12-03 17:00' AND
        timestamp '2059-12-03 22:00'
ORDER BY created_at, person_id ASC
