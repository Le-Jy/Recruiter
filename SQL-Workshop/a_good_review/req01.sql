INSERT INTO public.scrooge_eats_reviews (account_id, order_id, rating, review)
SELECT F.account_id, 10001, 5, 'Le gout etait interessant, melange avocat et dentifrice est peut commun dans un mojito. RAS pour le burger, un classique comme ce que je vais lacher dans les chiottes.'
FROM (SELECT account_id FROM public.scrooge_eats_orders
WHERE id = 10001) as F
