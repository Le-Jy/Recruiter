SELECT
    id,
    filename,
    CASE
        WHEN decrypted = false AND parent_id IN (
                        SELECT
                            id
                            FROM dtf.madelines_files_results
                            WHERE decrypted = true
                            GROUP BY id
                            )THEN 'File was successfully decrypted because its containing folder was successfully decrypted.'
        WHEN decrypted = true THEN 'File was successfully decrypted.'
        ELSE 'File remains encrypted.'
    END AS decryption_status
FROM dtf.madelines_files_results
ORDER BY id
