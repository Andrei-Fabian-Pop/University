-- alter table Account add age int
-- update Account set age = 29 where email = 'andreifabian@gmail.com'

-- 1
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age >= all (
    select A.age
    from Account A
)

-- 2
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age <= all (
    select A.age
    from Account A
)

-- 3
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age > any (
    select A.age
    from Account A
)

-- 4
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age < any (
    select A.age
    from Account A
)

-- 1
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age = (
    select max(B.age)
    from Account B
)

-- 2
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age = (
    select min(B.age)
    from Account B
)

-- 3
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age not in (
    select min(B.age)
    from Account B
)

-- 4
select A.firstName, A.lastName, A.email, A.age
from Account A
where A.age not in (
    select max(B.age)
    from Account B
)

