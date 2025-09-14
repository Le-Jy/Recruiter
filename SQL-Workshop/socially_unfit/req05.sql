SELECT DISTINCT sch.id, person_id, credits_change, action_description 
FROM public.people, public.social_credit_history AS sch
WHERE sch.date >= '2059-12-03 17:00'
AND sch.date <= '2059-12-03 22:00'
ORDER BY
    credits_change ASC,
    id ASC
LIMIT 10
