ALTER TABLE migration.companies
ADD COLUMN growth numeric(6,2) DEFAULT 0 NOT NULL CHECK (ABS(growth) <= 1000)
