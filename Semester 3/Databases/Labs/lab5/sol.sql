use master;

create table Ta (
    aid int primary key,
    a2 int unique,
    x int
)

create table Tb (
    bid int primary key,
    b2 int,
    x int
)

create table Tc (
    cid int primary key,
    aid int references Ta(aid),
    bid int references Tb(bid)
)

create or alter procedure populateTa(@rows int) as
    declare @max int
    set @max = @rows*5 + 25
    while @rows > 0 begin
        insert into Ta
            (aid, a2, x)
        values
            (@rows, @max, @rows%50)

        set @rows = @rows - 1
        set @max = @max - 5
    end
go

create or alter procedure populateTb(@rows int) as
    while @rows > 0 begin
        insert into Tb
            (bid, b2, x)
        values
            (@rows, @rows%69, @rows%420)

        set @rows = @rows - 1
    end
go

create or alter procedure populateTc(@rows int) as
    declare @aid int
    declare @bid int
    while @rows > 0 begin
        set @aid = (select top 1 aid from Ta order by newid())
        set @bid = (select top 1 bid from Tb order by newid())
        insert into Tc values (@rows, @aid, @bid)

        set @rows = @rows - 1
    end
go

exec populateTa @rows = 9000
exec populateTb @rows = 12000
exec populateTc @rows = 5000

create nonclustered index indexTa on Ta(x)
drop index indexTa on Ta

select * from Ta order by aid -- Clustered index scan
select * from Ta where aid = 1 -- Clustered index seek
select x from Ta order by x -- Non-clustered index scan
select a2 from Ta where a2 = 1 -- Non-clustered index seek
select x from Ta where a2 = 500 -- Key lookup

select * from Tb where b2 = 40 -- Clustered index scan

create nonclustered index indexTb on Tb(b2) include (bid, x)
drop index indexTb on Tb

select * from Tb where b2 = 40 -- Non-clustered index scan

create or alter view viewCluster as
    select top 1000 T1.x, T2.b2
    from Tc T3 join Ta T1 on T3.aid = T1.aid join Tb T2 on T3.bid = T2.bid
    where T2.b2 > 25 and T1.x < 25
go

select * from viewCluster