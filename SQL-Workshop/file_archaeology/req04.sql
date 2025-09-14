SELECT
    mf.parent_id AS folder_id,
    COUNT ( * ) AS nb_executables
FROM dtf.madelines_files AS mf
WHERE permissions LIKE '%x%'
GROUP BY parent_id
HAVING COUNT ( * ) >= 3
ORDER BY folder_id NULLS FIRST

