SELECT
    filename,
    size
FROM
    (
        SELECT AVG(SIZE)
        FROM dtf.madelines_files
    ) as F, dtf.madelines_files
WHERE
    F.AVG * 0.75 < size
ORDER BY size DESC
