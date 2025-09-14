SELECT DISTINCT
    CS.employee_id,
    P.id AS person_id,
    P.first_name,
    P.last_name
FROM
    nexus_stores.cashier_shifts AS CS
    RIGHT JOIN nexus_stores.employees AS E ON (CS.employee_id = E.id)
    JOIN public.people AS P ON (E.person_id = P.id)
WHERE
    CS.store_id = 78 AND
    start_timestamp::date = '2059-12-01'::date AND
    E.position = 'CASHIER' AND
    CS.employee_id NOT IN (
SELECT
    employee_id
FROM
    nexus_stores.cashier_shifts
WHERE
    employee_id IS NOT NULL AND
    start_timestamp = '2059-12-01 13:00:00'::timestamp AND
    end_timestamp = '2059-12-01 15:00:00'::timestamp AND
    store_id = 78
)
ORDER BY person_id DESC
