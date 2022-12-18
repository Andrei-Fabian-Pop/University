exec addToTables @tableName = 'Group'
exec addToTables @tableName = 'GroupList'

create or alter view getGroupNamesFromGroupList as
    select GL.name
    from GroupList GL inner join [Group] G on G.id = GL.groupID
    where G.id % 5 = 0
    group by GL.name
go

exec addToViews @viewName = 'getGroupNamesFromGroupList'
exec addToTests @testName = 'test3'
exec connectTableToTest @tableName = 'Group', @testName = 'test3', @rows = 500, @pos = 3
exec connectTableToTest @tableName = 'GroupList', @testName = 'test3', @rows = 500, @pos = 4
exec connectViewToTest @viewName = 'getGroupNamesFromGroupList', @testName = 'test3'

create or alter procedure populateTableGroup (@rows int) as
    while @rows > 0 begin
        insert into [Group]
            (id, name, description)
        values
            (@rows, 'testGr', 'testDes')
        set @rows = @rows - 1
    end
go

create or alter procedure populateTableGroupList (@rows int) as
    while @rows > 0 begin
        insert into GroupList
            (id, name, userID, groupID)
        values
            (@rows, 'test name' + str(@rows), 'test id', @rows)
        set @rows = @rows - 1
    end
go

execute runTest @testName = 'test3'

-- truncate table GroupList
-- delete from [Group] where 1=1

-- create or alter procedure populateTableAddress (@rows int) as
--     declare @idc int
--     while @rows > 0 begin
--         set @idc = (select top 1 SC.id from SupportedCountries SC order by newid())
--         insert into Address
--             (id, country, county, city, street, streetNum, areaCode)
--         values
--             (@rows,
--              (select SC.country from SupportedCountries SC where SC.id = @idc),
--              (select SC.continent from SupportedCountries SC where SC.id = @idc),
--              'Test City',
--              'Test Street',
--              @rows,
--              @rows)
--         set @rows = @rows - 1
--     end
-- go
--
-- create or alter procedure populateTableLogin (@rows int) as
--     while @rows > 0 begin
--         insert into Login
--             (id, password, alternativeLogin, lastLogin)
--         values
--             (@rows, 'Test Passwd', null, datetimefromparts(2004, 5, floor(rand() * 27) + 1, 14, 25, 10, 0))
--         set @rows = @rows - 1
--     end
-- go
--
-- create or alter procedure populateTableAccount (@rows int) as
--     while @rows > 0 begin
--         insert into Account
--             (email, firstName, middleName, lastName, mobile, fax, address, createdAt, login, age)
--         values
--             ('test@email' + str(@rows),
--              'Test First Name',
--              'Test Middle Name',
--              'Test Last Name',
--              'Test Mobile',
--              'Test Fax',
--              @rows,
--              datetimefromparts(2004, 5, floor(rand() * 27) + 1, 14, 25, 10, 0),
--              @rows,
--              20)
--         set @rows = @rows - 1
--     end
-- go
--
-- create or alter procedure populateTableUser (@rows int) as
--     while @rows > 0 begin
--         insert into [User]
--             (uid, account, contacts, subscriptions, reminders)
--         values
--             ('test@email' + str(@rows), 'test@email' + str(@rows), null, null, null);
--         set @rows = @rows - 1
--     end
-- go

-- execute runTest @testName = 'test3'
