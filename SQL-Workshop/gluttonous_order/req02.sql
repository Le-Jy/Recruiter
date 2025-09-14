INSERT INTO public.scrooge_eats_orders
SELECT 10000, F.id, NOW(), 0 FROM (SELECT F.id
    FROM (SELECT SEA.id FROM public.scrooge_eats_accounts AS SEA, public.companies AS C
        WHERE SEA.company_id = C.id
        AND C.name LIKE 'DTF') AS F) AS F
