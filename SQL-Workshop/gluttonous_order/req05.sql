INSERT INTO public.scrooge_eats_orders
SELECT 10001, F.id, NOW(), 0 FROM (SELECT F.id
    FROM (SELECT SEA.id FROM public.scrooge_eats_accounts AS SEA, public.companies AS C
        WHERE SEA.company_id = C.id
        AND C.name LIKE 'DTF') AS F) AS F;

INSERT INTO public.scrooge_eats_basket_items (order_id, item_id, quantity)
SELECT 10001, SEI.id, 1 FROM (
    SELECT id FROM public.scrooge_eats_items
    WHERE name LIKE 'Mojito'
    OR name LIKE 'Classic burger'
    ) AS SEI;
