-- get the names of all users that sent a message to themselves

select acc.firstName, acc.middleName, acc.lastName
from Account acc
where acc.email in (
    select UC.user1ID from UserConversation UC inner join [User] U on U.uid = UC.user1ID and U.uid = UC.user2ID
    group by UC.user1ID
)


-- get the subscription begin date of all premium users from romania
select PU.subscriptionBeginDate
from PremiumUsers PU
where PU.id in (
    select A.email from Account A inner join Address A2 on A2.id = A.address where A2.country = 'Romania'
    group by A.email
)
