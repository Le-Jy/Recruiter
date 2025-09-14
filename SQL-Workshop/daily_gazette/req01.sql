CREATE SCHEMA IF NOT EXISTS rr_times;

CREATE TABLE IF NOT EXISTS rr_times.locales (
    language_code varchar(2) CHECK (language_code SIMILAR TO '[a-z]{2}'),
    country_code varchar(2) CHECK (country_code SIMILAR TO '[A-Z]{2}'),
    name varchar(50) PRIMARY KEY,
    UNIQUE (language_code, country_code)
);

CREATE TABLE IF NOT EXISTS rr_times.translated_articles (
    id serial PRIMARY KEY,
    title text NOT NULL,
    body text NOT NULL
);
