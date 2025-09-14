CREATE RECURSIVE VIEW memorin.server_hierarchy(id, zone_id, core_count, ram, storage, data_center_id)
AS
    SELECT
        id,
        zone_id,
        core_count,
        ram,
        storage,
        id AS data_center_id
    FROM
        memorin.servers
    WHERE
        master_id IS NULL
    UNION ALL
    SELECT
        S.id,
        S.zone_id,
        S.core_count,
        S.ram,
        S.storage,
        SH.data_center_id
    FROM
        memorin.servers AS S
        JOIN server_hierarchy AS SH ON SH.id = S.master_id
