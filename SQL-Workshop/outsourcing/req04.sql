SELECT DISTINCT
        p.id as person_id,
        p.first_name,
        p.last_name,
        o.created_at,
        o.serving_time,
        o.created_at +
        (o.serving_time -
        COALESCE
        (
            (
            SELECT sr.amount
            FROM justice.sentence_reductions AS sr
            WHERE sr.outcome_id = o.id
            ), 0
        )
        ) * INTERVAL '1 month' AS release_date
INTO public.release_dates
FROM
    justice.trials AS t,
    justice.cases AS c,
    justice.outcomes AS o,
    public.people AS p,
    justice.defendants AS d,
    justice.sentence_reductions AS sr
WHERE
    o.outcome = 'GUILTY' AND
    t.case_id = c.id AND
    t.id = o.trial_id AND
    d.trial_id = t.id AND
    d.person_id = p.id
ORDER BY release_date DESC, o.serving_time DESC
