CREATE TYPE public.prefix AS enum (
    'MRS',
    'MS',
    'MR',
    'DR'
);

CREATE TABLE IF NOT EXISTS dtf.madelines_contacts (
    id serial PRIMARY KEY,
    title public.prefix,
    first_name text,
    last_name text,
    phone text,
    email text,
    favorite boolean,
    created_at timestamp
);
