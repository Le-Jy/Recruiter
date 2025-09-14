SELECT purchase_date, first_name, last_name, email, name, price, category
FROM nexus_stores.receipts AS R, nexus_stores.receipt_items AS RI, nexus_stores.products AS P
WHERE RI.receipt_id = R.id
AND RI.product_id = P.id
AND name ILIKE '%apple%'
AND email SIMILAR TO 's(a|e)m[a-z]{3,6}\_w[a-z]{6}[0-9]*@roger\_[a-z]+.[a-z]{3}'
