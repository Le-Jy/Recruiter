SELECT receipt_id, name, quantity, price
FROM nexus_stores.receipt_items AS RI, nexus_stores.receipts AS R, nexus_stores.products AS P
WHERE RI.product_id = P.id
AND RI.receipt_id = R.id
AND name ILIKE '%apple%'
AND quantity > 10
