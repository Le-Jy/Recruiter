SELECT
    GZ.name AS zone_name,
    COUNT (*) FILTER (WHERE SH.data_center_id = SH.id) AS data_center_count,
    COUNT (SH.id) AS total_servers,
    SUM (core_count) AS total_cores,
    SUM (ram) AS total_ram,
    SUM (storage) AS total_storage
    FROM
    memorin.geographic_zones AS GZ
    JOIN memorin.server_hierarchy AS SH ON GZ.id = SH.zone_id
GROUP BY zone_name
ORDER BY data_center_count DESC, total_servers DESC, zone_name
