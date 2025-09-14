SELECT
    AVG(COALESCE(NULLIF(COALESCE(rsa_time,0), 0),(SELECT max(rsa_time) FROM dtf.madelines_files_results)))::numeric(15, 2) as avg_rsa_time,
    AVG(COALESCE(NULLIF(COALESCE(hyper_pulse_time,0),0), (SELECT max(hyper_pulse_time) FROM dtf.madelines_files_results)))::numeric(15, 2) as avg_hyper_pulse_time,
    AVG(COALESCE(NULLIF(COALESCE(quantum_x_time,0),0), (SELECT max(quantum_x_time) FROM dtf.madelines_files_results)))::numeric(15, 2) as avg_quantum_x_time,
    AVG(COALESCE(NULLIF(COALESCE(aes_time,0),0), (SELECT max(aes_time) FROM dtf.madelines_files_results)))::numeric(15, 2) as avg_aes_time,
    AVG(COALESCE(NULLIF(COALESCE(d_crypt_time,0),0), (SELECT max(d_crypt_time) FROM dtf.madelines_files_results)))::numeric(15, 2) as avg_d_crypt_time
FROM
    dtf.madelines_files_results
