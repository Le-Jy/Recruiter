CREATE SCHEMA IF NOT EXISTS nexus;
CREATE SCHEMA IF NOT EXISTS nexus_it;
CREATE SCHEMA IF NOT EXISTS techwave;
CREATE SCHEMA IF NOT EXISTS finstar;
CREATE SCHEMA IF NOT EXISTS nexus_food;
CREATE SCHEMA IF NOT EXISTS guardforce;

CREATE TYPE nexus.position AS ENUM (
    'JUNIOR',
    'SENIOR',
    'MANAGER',
    'DIRECTOR'
);

CREATE TYPE nexus.relationship_type AS ENUM (
    'PARENT',
    'SUBSIDIARY',
    'AFFILIATE'
);

CREATE TYPE nexus_food.nutriscore AS ENUM (
    'A',
    'B',
    'C',
    'D',
    'E'
);

CREATE TABLE IF NOT EXISTS nexus.employees (
    id serial,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);

CREATE TABLE IF NOT EXISTS nexus_it.employees (
    id serial,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);

CREATE TABLE IF NOT EXISTS techwave.employees (
    id serial,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);

CREATE TABLE IF NOT EXISTS finstar.employees (
    id serial,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);

CREATE TABLE IF NOT EXISTS nexus_food.employees (
    id serial,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);

CREATE TABLE IF NOT EXISTS guardforce.employees (
    id serial,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);


CREATE TABLE IF NOT EXISTS nexus.nexus_relations (
    id serial,
    parent_company varchar(25),
    child_company varchar(25),
    relationship_type nexus.relationship_type
);

CREATE TABLE IF NOT EXISTS nexus_it.software_assets (
    id serial,
    software_name varchar(50),
    license_key uuid,
    expiration_date date
);

CREATE TABLE IF NOT EXISTS techwave.project_milestones (
    id serial,
    milestone_name varchar(50),
    due_date date,
    completion_status boolean
);

CREATE TABLE IF NOT EXISTS finstar.investments (
    id serial,
    investment_name varchar(50),
    investment_type varchar(25),
    amount_invested numeric(15, 5),
    date_invested date
);

CREATE TABLE IF NOT EXISTS nexus_food.products (
    id serial,
    product_name varchar(25),
    product_nutriscore nexus_food.nutriscore
);

CREATE TABLE IF NOT EXISTS guardforce.incident_reports (
    id serial,
    incident_description text,
    incident_date timestamp,
    incident_location varchar(50),
    reported_by varchar(50)
);
