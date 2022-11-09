-- print countries with at least one user
select A.country, count(*) as country
from Address A
group by A.country
having count(*) >= 1

-- print countries with the most users, including banned countries
select A.country, BC.country, count(*) as country
from Address A full outer join BannedCountries BC on A.country != BC.country
group by A.country, BC.country
having count(*) = (
    select max(t.C)
    from (
        select count(*) C
        from Address A full outer join BannedCountries BC on A.country != BC.country
        group by A.country, BC.country
    ) t
)

-- print the countries and the nr of accounts from that country
select A.country, count (*) as acc_per_country
from Address A
group by A.country


