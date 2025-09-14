CREATE SCHEMA migration;

CREATE TABLE IF NOT EXISTS migration.jobs (LIKE public.jobs INCLUDING ALL);
CREATE TABLE IF NOT EXISTS migration.companies (LIKE public.companies INCLUDING ALL);
CREATE TABLE IF NOT EXISTS migration.patients_records (LIKE public.patients_records INCLUDING ALL);
CREATE TABLE IF NOT EXISTS migration.medical_record_entries (LIKE public.medical_record_entries INCLUDING ALL);

INSERT INTO migration.jobs SELECT * FROM public.jobs;
INSERT INTO migration.companies SELECT * FROM public.companies;
INSERT INTO migration.patients_records SELECT * FROM public.patients_records;
INSERT INTO migration.medical_record_entries SELECT * FROM public.medical_record_entries;
