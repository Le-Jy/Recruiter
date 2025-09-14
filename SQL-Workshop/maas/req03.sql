CREATE VIEW memorin.zoned_devices_logs AS
SELECT
    DL.device_serial,
    DL.version_id,
    DL.zone_id AS zone_id,
    DL.latitude AS lat,
    DL.longitude AS long,
    DL.temperature AS temp,
    DL.battery_percentage AS battery,
    DL.signal_strength
FROM
    memorin.device_logs AS DL
WHERE
    DL.temperature BETWEEN 34 AND 45 AND
    DL.signal_strength >= 0 AND DL.signal_strength <= 5 AND
    DL.battery_percentage BETWEEN 0 AND 100 AND
    EXISTS (
        SELECT
            1
        FROM memorin.geographic_zones AS GZ
        WHERE
            DL.zone_id = GZ.id AND
            DL.latitude BETWEEN GZ.min_latitude AND GZ.max_latitude AND
            DL.longitude BETWEEN GZ.min_longitude AND GZ.max_longitude
    )
        AND DL.device_serial IN
    (
        SELECT D.serial_number FROM memorin.devices AS D
        WHERE D.deactivated_at IS NULL
    )
    AND EXISTS
    (
        SELECT 1 FROM memorin.device_versions AS DV
        WHERE DL.version_id = DV.id
    )
WITH CHECK OPTION;
