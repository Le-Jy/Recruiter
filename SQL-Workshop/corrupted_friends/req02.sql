INSERT INTO dtf.madelines_contacts
SELECT
    id,
    upper(split_part(regexp_replace(full_name, '[^ a-zA-Z]', '', 'g'), ' ',
            1))::public.prefix AS title,
    initcap(split_part(regexp_replace(full_name, '[^ a-zA-Z]', '', 'g'), ' ', 2)) AS first_name,
    initcap(split_part(regexp_replace(full_name, '[^ a-zA-Z]', '', 'g'), ' ', 3)) AS last_name,
    concat(
        lpad(split_part(regexp_replace(
        regexp_replace(phone, '[^-.0-9]', '', 'g'), '-', '.', 'g'), '.', 1), 3, '0'),
        '.',
        lpad(split_part(regexp_replace(
        regexp_replace(phone, '[^-.0-9]', '', 'g'), '-', '.', 'g'), '.', 2), 3, '0'),
        '.',
        lpad(split_part(regexp_replace(
        regexp_replace(phone, '[^-.0-9]', '', 'g'), '-', '.', 'g'), '.', 3), 3, '0')
    ) AS phone,
    email,
    favorite = '1',
    created_at::timestamp
FROM dtf.madelines_contacts_corrupted
