SELECT RES.id, RES.reservation_id
FROM gusto_guests as RES,
    (SELECT id FROM gusto_reservations
    WHERE cancelled = False
    AND reservation_date >= '2059-12-03 18:00:00'
    AND reservation_date <= '2059-12-03 21:00:00') AS sus_res_id
WHERE sus_res_id.id = RES.reservation_id
