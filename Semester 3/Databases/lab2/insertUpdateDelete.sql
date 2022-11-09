USE master;

INSERT INTO Address
(id, country, county, city, street, streetNum, areaCode)
VALUES
    (0, 'Romania', 'Cluj', 'Cluj-Napoca', 'Aurel Vlaicu', 115, 46842),
    (1, 'Englandia', 'Lancashire', 'Manchester', 'Queens', 69, 41526),
    (2, 'Irlandia', 'Dublin', 'Dublin', 'OConnor Street', 14, 987456),
    (3, 'Austria', 'Vienna', 'Vienna', 'Donaufelder Strase', 222, 36984);

INSERT INTO Account
    (email, firstName, middleName, lastName, mobile, fax, address, createdAt, login)
VALUES
    ('andreifabian@gmail.com', 'Andrei', 'Fabian', 'Pop', '+40696969696', NULL, 0, '20120618 10:34:09 AM', 0),
    ('andrei2@gmail.com', 'Andrei', 'Miaw', 'Pop', '+40000111222', NULL, 1, '20120618 10:34:09 AM', 1),
    ('andrei3@gmail.com', 'Andrei', 'Miaw', 'ln', '+40111222333', 'idk 555', 2, '20120618 10:34:09 AM', 2),
    ('andrei4@gmail.com', 'Andri', 'Fabian', 'ln', '+40222333444', NULL, 3, '20120618 10:34:09 AM', 3);

INSERT INTO [User]
    (uid, account, reminders, contacts, subscriptions)
VALUES
    ('andreifabian@gmail.com', 'andreifabian@gmail.com', NULL, NULL, NULL),
    ('andrei2@gmail.com', 'andrei2@gmail.com', NULL, NULL, NULL),
    ('andrei3@gmail.com', 'andrei3@gmail.com', NULL, NULL, NULL),
    ('andrei4@gmail.com', 'andrei4@gmail.com', NULL, NULL, NULL);

INSERT INTO Login
    (id, password, alternativeLogin, lastLogin)
VALUES
    (0, 'MyStrongPassword0', 'microsoftAccount', '20120618 10:34:09 AM'),
    (1, 'MyStrongPassword1', 'microsoftAccount', '20120619 10:34:09 AM'),
    (2, 'MyStrongPassword2', NULL, '20120620 10:34:09 AM'),
    (3, 'MyStrongPassword3', 'microsoftAccount', '20120621 10:34:09 AM');

INSERT INTO Subscription
    (id, name, interval)
VALUES
    (0, 'Email administrative newsletter', '20120621 10:34:09 AM');

UPDATE Account SET firstName = 'Andrei' WHERE firstName = 'Andri'
UPDATE [User] SET subscriptions = 0 WHERE subscriptions IS NULL
UPDATE Login SET alternativeLogin = NULL WHERE alternativeLogin IS NULL

DELETE FROM Login where id = 2;
DELETE FROM Address where street like '%Strase'

INSERT INTO Login VALUES (2, 'MyStrongPassword2', NULL, '20120620 10:34:09 AM');
INSERT INTO Address VALUES (3, 'Austria', 'Vienna', 'Vienna', 'Donaufelder Strase', 222, 36984);

