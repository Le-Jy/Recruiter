SELECT
    COUNT(*) - (
        SELECT COUNT(*)
        FROM nexus_stores.cashier_shifts
        WHERE employee_id IS NOT NULL
    ) AS null_employee_id_rows_count,
    COUNT(*) - (
        SELECT COUNT(*)
        FROM nexus_stores.cashier_shifts
        WHERE store_id IS NOT NULL
    ) AS null_store_id_rows_count
FROM
    nexus_stores.cashier_shifts AS S1
    JOIN nexus_stores.cashier_shifts AS S2
    ON (S1.id = S2.id); --AS CS LEFT JOIN nexus_stores.employees AS E ON (CS.employee_id = E.id)) AS F LEFT JOIN nexus_stores.sales AS S ON (F.store_id = S.store_id)
