CREATE TYPE rr_times.rubric_theme AS enum (
    'TECHNOLOGY',
    'ECONOMY',
    'HEALTH',
    'SPORT',
    'CULTURE',
    'POLITICS',
    'SCIENCE',
    'TRAVEL',
    'SOCIETY',
    'ENVIRONMENT',
    'EDUCATION',
    'MEDIA',
    'FASHION',
    'ARCHITECTURE',
    'BUSINESS',
    'SPACE'
);

CREATE TABLE IF NOT EXISTS rr_times.rubrics (
    id serial PRIMARY KEY,
    theme text NOT NULL,
    nb_columns integer NOT NULL,
    issue_id integer NOT NULL REFERENCES rr_times.issues (id) ON DELETE CASCADE,
    UNIQUE (theme, issue_id)
);
