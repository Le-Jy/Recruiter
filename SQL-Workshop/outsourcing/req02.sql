SELECT
        p.id as person_id,
        p.first_name,
        p.last_name,
        p.birth_date,
        o.created_at AS conviction_date,
        o.serving_time,
        o.created_at + o.serving_time * INTERVAL '1 month' <= DATE '2059-12-03' AS could_be_released
INTO public.outcome_status
FROM
    justice.trials AS t,
    justice.cases AS c,
    justice.outcomes AS o,
    public.people AS p,
    justice.defendants AS d
WHERE
    o.outcome = 'GUILTY' AND
    c.classification = 'CRIME' AND
    t.case_id = c.id AND
    t.id = o.trial_id AND
    d.trial_id = t.id AND
    d.person_id = p.id
