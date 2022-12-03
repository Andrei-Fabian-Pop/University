-- get email and password from all users
SELECT U.email, L.password FROM Account U INNER JOIN Login L ON U.login = L.id


select distinct Acc.email
from Account Acc
    inner join Address A on A.id = Acc.address
    inner join Login L on L.id = Acc.login
    inner join [User] U on Acc.email = U.account
    inner join Subscription S on S.id = U.subscriptions

select U.account from PremiumUsers P left join [User] U on U.uid = P.id

select U.account from PremiumUsers P full join [User] U on U.uid = P.id

-- same as left join
select U.account from [User] U right join PremiumUsers P on U.uid = P.id

