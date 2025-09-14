CREATE TABLE banking_transactions_poc
(
    id serial PRIMARY KEY,
    sender varchar(22) NOT NULL CHECK (sender SIMILAR TO 'RR[0-9]{2}[A-Z]{4}[0-9]{14}'),
    receiver varchar(22) NOT NULL CHECK (receiver SIMILAR TO 'RR[0-9]{2}[A-Z]{4}[0-9]{14}'),
    amount numeric(16, 2) NOT NULL CHECK (amount > 0),
    CHECK (sender <> receiver)
);
