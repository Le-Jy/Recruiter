INSERT INTO public.scrooge_eats_reviews (account_id, rating, review)
SELECT F.account_id, 5, 'Sympatoche le service, STADE TOULOUSAIN RPZ'
FROM (SELECT account_id FROM public.scrooge_eats_orders
WHERE id = 10001) as F
