-- emails of ppl with subscription

select ACC.email
from (
    select A.email
    from Account A
) ACC
where ACC.email in (
    select U.uid
    from [User] U
    where U.subscriptions = 0
)


-- countries in use and in banned countries

select Ad.country
from (
    select A.country
    from Address A
) Ad
where Ad.country in (
    select BC.country
    from BannedCountries BC
    where Ad.country != BC.country
)
