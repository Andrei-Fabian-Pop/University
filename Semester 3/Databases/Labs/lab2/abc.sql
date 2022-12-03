-- UNION
SELECT id FROM Login WHERE alternativeLogin IS NULL OR lastLogin > '20120621 10:34:09 AM'
UNION
SELECT address FROM Account WHERE email = 'andreifabian@gmail.com'

-- OR
SELECT email FROM Account WHERE middleName = 'Fabian' OR middleName = 'Miaw'

-- INTERSECT
SELECT email FROM Account
INTERSECT
SELECT uid FROM [User]

-- OR
SELECT password FROM Login WHERE id IN (SELECT login FROM Account);

-- IN
SELECT password FROM Login WHERE id IN (SELECT login FROM Account);

-- EXCEPT
SELECT country FROM Address
EXCEPT
SELECT country FROM Address WHERE country = 'Englandia'

-- NOT IN
SELECT country FROM Address WHERE country NOT IN (SELECT country FROM Address WHERE country LIKE '%dia')
