USE master;

-- DROP TABLE *

CREATE TABLE [Address]
(
    id        int         NOT NULL PRIMARY KEY,
    country   varchar(50) NOT NULL,
    county    varchar(50) NOT NULL,
    city      varchar(50) NOT NULL,
    street    varchar(50) NOT NULL,
    streetNum int         NOT NULL,
    areaCode  int         NOT NULL,
);

CREATE TABLE [Login]
(
    id               int PRIMARY KEY,
    email            varchar(256) NOT NULL UNIQUE,
    [password]       varchar(100) NOT NULL,
    alternativeLogin varchar(100),
    lastLogin        DATETIME     NOT NULL,
)

CREATE TABLE [Account]
(
    email      varchar(256) NOT NULL PRIMARY KEY,
    firstName  varchar(100) NOT NULL,
    middleName varchar(100),
    lastName   varchar(100) NOT NULL,
    mobile     int          NOT NULL,
    fax        int,
    [address]  int UNIQUE   NOT NULL FOREIGN KEY REFERENCES Address (id) ON DELETE CASCADE,
    createdAt  DATETIME     NOT NULL,
    [login]    int          NOT NULL REFERENCES Login (id) ON DELETE CASCADE,
);

CREATE TABLE [Reminder]
(
    id        int PRIMARY KEY,
    [message] varchar(500) NOT NULL,
    [date]    DATETIME     NOT NULL,
)

CREATE TABLE [Subscription]
(
    id         int PRIMARY KEY NOT NULL,
    [name]     varchar(100)    NOT NULL,
    [interval] DATETIMEOFFSET  NOT NULL,
)

CREATE TABLE [Email]
(
    id        bigint PRIMARY KEY NOT NULL,
    [from]    varchar(256)       NOT NULL,
    [to]      varchar(256)       NOT NULL,
    [message] varchar            NOT NULL,
    [date]    datetime           NOT NULL,
)

CREATE TABLE [User]
(
    uid           varchar(256) NOT NULL PRIMARY KEY,
    account       varchar(256) NOT NULL FOREIGN KEY REFERENCES Account (email) ON DELETE CASCADE,
    reminders     int REFERENCES Reminder (id) ON DELETE CASCADE,
    contacts      varchar(256),
    subscriptions int REFERENCES Subscription (id) ON DELETE CASCADE,
    emails        bigint FOREIGN KEY REFERENCES Email (id),
);

CREATE TABLE [Group]
(
    id            int PRIMARY KEY NOT NULL,
    [name]        varchar(100)    NOT NULL,
    [description] varchar(100),
    [user]        varchar(256) FOREIGN KEY REFERENCES [User] (uid),
)

CREATE TABLE [GroupList]
(
    id      int PRIMARY KEY NOT NULL,
    [name]  varchar(100)    NOT NULL,
    userID  varchar(256) FOREIGN KEY REFERENCES [User] (uid),
    groupID int FOREIGN KEY REFERENCES [Group] (id),
)

CREATE TABLE [UserConversation]
(
    id       int PRIMARY KEY NOT NULL,
    messages varchar(256)    NOT NULL,
    user1ID  varchar(256) FOREIGN KEY REFERENCES [User] (uid),
    user2ID  varchar(256) FOREIGN KEY REFERENCES [User] (uid),
)

