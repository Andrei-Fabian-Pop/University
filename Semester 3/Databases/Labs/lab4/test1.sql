use master;

exec addToTables @tableName = 'Reminder'

create or alter view getReminderDates as
    select date, count(*) as nr_of_reminders
    from Reminder
    group by date
go

exec addToViews @viewName = 'getReminderDates'
exec addToTests @testName = 'test1'
exec connectTableToTest @tableName = 'Reminder', @testName = 'test1', @rows = 1000, @pos = 1
exec connectViewToTest @viewName = 'getReminderDates', @testName = 'test1'

create or alter procedure populateTableReminder (@rows int) as
    while @rows > 0 begin
        insert into Reminder
            (id, message, date)
        values
            (@rows, 'Testing', datetimefromparts(2004, 5, floor(rand() * 27)+1, 14, 25, 10, 0))
        set @rows = @rows - 1
    end
go

execute runTest @testName = 'test1'