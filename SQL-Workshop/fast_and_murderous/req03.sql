SELECT person_id, matched.id, content, description
FROM justice.testimonies, justice.cases AS matched
WHERE content LIKE '%Nexus N3%'
AND (description SIMILAR TO '%speed%'
OR description LIKE '%fast%'
OR description LIKE '%reckless%')
AND matched.id = case_id
