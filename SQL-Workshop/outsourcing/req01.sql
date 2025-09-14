SELECT t.id AS trial_id, c.id as case_id, c.classification, c.description
INTO public.definitive_trials
FROM justice.trials AS t, justice.cases AS c
WHERE t.status = 'FINISHED' AND t.case_id = c.id
ORDER BY c.classification, c.id
