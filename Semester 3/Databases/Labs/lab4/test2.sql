use master;

exec addToTables @tableName = 'UserConversation'
-- exec addToTables @tableName = 'User'

create or alter view getMessagesFromUsers as
    select U.account, UC.messages
    from UserConversation UC inner join [User] U on U.uid = UC.user1ID
go

exec addToViews @viewName = 'getMessagesFromUsers'
exec addToTests @testName = 'test2'
exec connectTableToTest @tableName = 'UserConversation', @testName = 'test2', @rows = 600, @pos = 10
-- exec connectTableToTest @tableName = 'User', @testName = 'test2', @rows = 700, @pos = 11
exec connectViewToTest @viewName = 'getMessagesFromUsers', @testName = 'test2'

-- create or alter procedure populateTableUsers (@rows int) as
--     while @rows > 0 begin
--         insert into [User]
--             (uid, account, contacts, subscriptions)
--         values
--             ('test' + str(@rows) + '@account', 'test' + str(@rows) + '@account', null, null)
--         set @rows = @rows - 1
--     end
-- go
-- drop procedure populateTableUsers

create or alter procedure populateTableUserConversation (@rows int) as
    while @rows > 0 begin
        insert into UserConversation
            (id, messages, user1ID, user2ID)
        values
            (@rows, 'test message', (select top 1 uid from [User] order by newid()), (select top 1 uid from [User] order by newid()))
        set @rows = @rows - 1
    end
go

-- alter table PremiumUsers drop constraint FK__PremiumUsers__id__3D9E16F4
-- alter table [User] add reminders int
execute populateTableUserConversation @rows = 20

execute runTest @testName = 'test2'
