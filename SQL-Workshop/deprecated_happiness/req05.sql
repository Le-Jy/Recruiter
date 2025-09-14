ALTER TABLE migration.medical_record_entries
ALTER COLUMN description TYPE varchar(100)
USING
CASE WHEN LENGTH(description) > 100 THEN SUBSTRING(description, 1, 97) || '...'
ELSE description
END
