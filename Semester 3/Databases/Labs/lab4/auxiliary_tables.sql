use master;

create table Tests (
    testID int primary key identity (1,1),
    Name varchar(50)
)

create table Tables (
    tableID int primary key identity (1,1),
    Name varchar(50)
)

create table Views (
    viewID int primary key identity (1,1),
    Name varchar(50)
)

create table TestTables (
    testID int,
    tableID int,
    nrOfRows int,
    position int
)

create table TestViews (
    testID int,
    viewID int
)

create table TestRuns (
    RunID int identity (1,1),
    Description varchar(256),
    StartAt datetime2,
    EndAt datetime2
)

create table TestRunTables (
    TestRunID int,
    TableID int,
    StartAt datetime2,
    EndAt datetime2
)

create table TestRunViews (
    TestRunID int,
    ViewID int,
    StartAt datetime2,
    EndAt datetime2
)
