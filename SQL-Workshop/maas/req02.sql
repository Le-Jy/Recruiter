CREATE TEMPORARY VIEW devices_metrics AS
SELECT
    DL.device_serial,
    DL.version_id,
    DL.id AS log_id,
    DL.latitude AS lat,
    DL.longitude AS long,
    DL.temperature AS temp,
    DL.battery_percentage AS battery,
    DL.signal_strength
FROM
    memorin.devices AS D
    JOIN memorin.device_logs AS DL ON D.serial_number = DL.device_serial AND
    D.deactivated_at IS NULL
    JOIN memorin.device_versions AS DV ON DV.id = DL.version_id
ORDER BY DL.device_serial, DV.released_at DESC, log_id ASC
