INSERT INTO public.scrooge_eats_basket_items (order_id, item_id, quantity)
SELECT 10000, SEI.id, 1 FROM (
    SELECT id FROM public.scrooge_eats_items
    WHERE name LIKE 'Kinder Bueno White'
    ) AS SEI
