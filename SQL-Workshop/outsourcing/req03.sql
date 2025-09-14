SELECT
        p.id as person_id,
        p.first_name,
        p.last_name,
        p.birth_date,
        c.classification,
        c.description
INTO TEMPORARY not_guilty
FROM
    justice.trials AS t,
    justice.cases AS c,
    justice.outcomes AS o,
    public.people AS p,
    justice.defendants AS d
WHERE
    o.outcome = 'NOT_GUILTY' AND
    t.case_id = c.id AND
    t.id = o.trial_id AND
    d.trial_id = t.id AND
    d.person_id = p.id
