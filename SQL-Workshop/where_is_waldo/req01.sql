CREATE TABLE dtf.shifts_and_sales_78
AS SELECT
    S.id AS sales_id,
    product_id,
    CS.checkout_id,
    sale_timestamp,
    CS.id as shift_id,
    employee_id,
    start_timestamp AS shift_start_timestamp,
    end_timestamp AS shift_end_timestamp
FROM
    nexus_stores.sales AS S
    JOIN nexus_stores.cashier_shifts AS CS
    ON S.checkout_id = CS.checkout_id AND  S.sale_timestamp BETWEEN
    CS.start_timestamp AND CS.end_timestamp

WHERE
    '2059-12-01 14:47:07' BETWEEN CS.start_timestamp AND CS.end_timestamp AND
     CS.store_id = 78
