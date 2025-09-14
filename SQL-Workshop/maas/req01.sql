CREATE VIEW memorin.devices_summary AS
SELECT
    COUNT (*) AS total_devices,
    COUNT (*) FILTER (WHERE deactivated_at IS NULL) AS active_devices,
    COUNT (*) FILTER (WHERE deactivated_at IS NOT NULL) AS inactive_devices
FROM memorin.devices
