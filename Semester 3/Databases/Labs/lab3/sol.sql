-- a
create procedure setBannedCountriesToTinyInt as
    alter table BannedCountries alter column id tinyint
go

create procedure setBannedCountriesToInt as
    alter table BannedCountries alter column id int
go

-- b
create procedure addBannedCountriesContinent as
    alter table BannedCountries add continent varchar(64)
go

create procedure removeBannedCountriesContinent as
    alter table BannedCountries drop column continent
go

-- c
create procedure addDefaultBannedCountriesContinent as
    alter table BannedCountries add constraint DEFAULT0 default('None') for continent
go

create procedure removeDefaultBannedCountriesContinent as
    alter table BannedCountries drop constraint DEFAULT0
go

-- g
create procedure addUselessTable as
    create table uselessTable (
        name varchar(50) not null,
        sk varchar(50) not null, -- second key
        num int,

        constraint USELESS_TABLE_PRIMARY_KEY primary key (name)
    )
go

create procedure removeUselessTable as
    drop table uselessTable
go

-- d
create procedure addSecondKeyAsPrimary as
    alter table uselessTable drop constraint USELESS_TABLE_PRIMARY_KEY
    alter table uselessTable add constraint USELESS_TABLE_PRIMARY_KEY primary key (name, sk)
go

create procedure removeSecondKeyAsPrimary as
    alter table uselessTable drop constraint USELESS_TABLE_PRIMARY_KEY
    alter table uselessTable add constraint USELESS_TABLE_PRIMARY_KEY primary key (name)
go

-- e
create procedure addCandidateKey as
    alter table uselessTable add constraint USELESS_CANDIDATE_KEY unique (num)
go

create procedure removeCandidateKey as
    alter table uselessTable drop constraint USELESS_CANDIDATE_KEY
go

-- f
create procedure addForeignKey as
    alter table uselessTable add constraint USELESS_FOREIGN_KEY foreign key (num) references BannedCountries(id)
go

create procedure removeForeignKey as
    alter table uselessTable drop constraint USELESS_FOREIGN_KEY
go

-- version control
create table versionTable (
    version int
)

insert into versionTable values (1) -- init

create table procedureTable (
    fromVersion int,
    toVersion int,
    primary key (fromVersion, toVersion),
    nameProcedure varchar(max)
)

insert into procedureTable
    (fromVersion, toVersion, nameProcedure)
VALUES
    (1, 2, 'setBannedCountriesToTinyInt'),
    (2, 1, 'setBannedCountriesToInt'),
    (2, 3, 'addBannedCountriesContinent'),
    (3, 2, 'removeBannedCountriesContinent'),
    (3, 4, 'addDefaultBannedCountriesContinent'),
    (4, 3, 'removeDefaultBannedCountriesContinent'),
    (4, 5, 'addUselessTable'),
    (5, 4, 'removeUselessTable'),
    (5, 6, 'addSecondKeyAsPrimary'),
    (6, 5, 'removeSecondKeyAsPrimary'),
    (6, 7, 'addCandidateKey'),
    (7, 6, 'removeCandidateKey'),
    (7, 8, 'addForeignKey'),
    (8, 7, 'removeForeignKey');

create procedure toVersion(@newVersion int) as
    declare @curr int
    declare @var varchar(max)
    select @curr=version as cv
    from versionTable

    if @newVersion > (select max(toVersion) as m from procedureTable)
        raiserror ('Bad version', 10, 1)

    while @curr > @newVersion begin
        select @var=nameProcedure as v from procedureTable where fromVersion=@curr and toVersion=@curr-1
        exec (@var)
        set @curr=@curr-1
    end

    while @curr < @newVersion begin
        select @var=nameProcedure as vnP from procedureTable where fromVersion=@curr and toVersion=@curr+1
        exec (@var)
        set @curr=@curr+1
    end

    update versionTable set version=@newVersion
go

execute toVersion @newVersion = 1
