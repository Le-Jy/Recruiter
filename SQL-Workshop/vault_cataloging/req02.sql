SELECT
    id,
    size as stored_size,
    decrypted,
    CASE
        WHEN size IS NULL AND decrypted = true THEN
            (
                SELECT
                    AVG(size) FILTER (WHERE decrypted = true AND parent_id != 0)
                FROM dtf.madelines_files_results
            )::bigint
        WHEN size IS NULL AND decrypted = false THEN
            (
                SELECT
                    AVG(size) FILTER (WHERE decrypted = false AND parent_id != 0)
                FROM dtf.madelines_files_results
            )::bigint
        ELSE size
    END AS calculated_size
FROM dtf.madelines_files_results
WHERE parent_id != 0
ORDER BY id
