SELECT
    filename,
    size
FROM (
    SELECT
    max(size) FILTER (WHERE created_at BETWEEN '2059-11-27'::timestamp
                    AND '2059-12-03'::timestamp)
    FROM dtf.madelines_files) AS F, dtf.madelines_files
WHERE
        size = F.max AND
        created_at BETWEEN '2059-11-27'::timestamp
                    AND '2059-12-03'::timestamp
ORDER BY filename
