INSERT INTO nexus_stores.sales
SELECT '01234567', 3, '68cdd3ec', 78, '2059-12-01 14:47:07'::timestamp;

INSERT INTO nexus_stores.cashier_shifts
SELECT '01234567', '68cdd3ec', NULL, 78, '2059-12-01 13:00:00'::timestamp, '2059-12-01 15:00:00'::timestamp;
