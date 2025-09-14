ALTER TABLE migration.patients_records
ADD COLUMN person_id integer;

UPDATE migration.patients_records AS PR
SET person_id = PI.person_id
FROM medical_confidential.patients_ids AS PI
WHERE PI.patient_id = PR.id;

ALTER TABLE migration.patients_records
ADD CONSTRAINT frj_s_constraint FOREIGN KEY (person_id) REFERENCES public.people (id);

ALTER TABLE migration.patients_records
ALTER COLUMN person_id SET NOT NULL;
