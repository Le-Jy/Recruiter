CREATE MATERIALIZED VIEW memorin.outdated_devices AS
    SELECT
        D.serial_number,
        D.version_id,
        DV.released_at,
        DV.eol_timestamp,
        (
            SELECT
                COUNT (DV2.id)
            FROM memorin.device_versions AS DV2
            WHERE DV2.released_at >= DV.eol_timestamp
        ) AS versions_behind
    FROM
        memorin.devices AS D
        JOIN memorin.device_versions AS DV ON D.version_id = DV.id
    WHERE
        DV.eol_timestamp IS NOT NULL AND
        D.deactivated_at IS NULL
ORDER BY versions_behind DESC, serial_number
