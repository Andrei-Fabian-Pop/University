//
// Created by andre on 19/03/2022.
//

#pragma once
#include "../Service/Service.h"
#include "../ExceptionsAndValidators/Validator.h"
#include "../ExceptionsAndValidators/Exception.h"
#include <iostream>
#include <exception>
//#include <windows.h>
//#include <shellapi.h>
#include <utility>
#include <algorithm>

class UI {
protected:
    Service service;
public:
    explicit UI(const Service& service);
    ~UI();
    static int get_user_input();
};

class Admin : public UI {
private:
    using UI::service;
    const unsigned short MAX_OPTION = 4;
public:
    explicit Admin(const Service &service);
    ~Admin();

    void start();
    static void print_options();

    void add();
    void remove();
    void update();
    void print_all();
};

class Client : public UI {
private:
    using UI::service;
    const unsigned short MAX_OPTION = 5;
public:
    explicit Client(const Service &service);
    ~Client();

    void start();
    static void print_options();

    void print_by_presenter();
    void delete_from_playlist();
    void print_watchlist();
    void save();
    void open();
};
