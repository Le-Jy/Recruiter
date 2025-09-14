SELECT
    CS.id,
    C.id AS checkout_id,
    CS.employee_id,
    CS.store_id AS shift_store_id,
    C.store_id AS checkout_store_id,
    CS.start_timestamp,
    CS.end_timestamp
FROM nexus_stores.checkouts AS C
    RIGHT JOIN nexus_stores.cashier_shifts AS CS ON (C.id = CS.checkout_id)
