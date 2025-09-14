SELECT first_name, last_name, birth_date, job_id, social_credit_balance
FROM public.people
WHERE death_date IS NULL
AND job_id IS NOT NULL
AND social_credit_balance > 0
ORDER BY
    social_credit_balance DESC,
    birth_date DESC,
    job_id ASC
LIMIT 100
OFFSET 200
