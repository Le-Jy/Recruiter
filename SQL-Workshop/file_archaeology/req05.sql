SELECT
    owner,
    COUNT (*) AS num_files
FROM dtf.madelines_files
GROUP BY owner
HAVING COUNT (*) = (
    SELECT
    MIN (F.toto)
    FROM
    (
        SELECT
        COUNT ( * ) AS toto
        FROM dtf.madelines_files AS mf
        GROUP BY mf.owner
    ) AS F
)
ORDER BY owner
