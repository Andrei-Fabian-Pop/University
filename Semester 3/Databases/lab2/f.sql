-- print all users that sent messages

select A.email
from Account A
where exists (
    select *
    from UserConversation UC
    where UC.user1ID = A.email
)

-- select all users with subscriptions

select U.account
from [User] U
where exists (
    select *
    from Subscription S
    where U.subscriptions = S.id
)
