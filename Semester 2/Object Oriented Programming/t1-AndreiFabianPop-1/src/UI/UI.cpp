//
// Created by andre on 07/04/2022.
//

#include "UI.h"

#include <utility>

void UI::start() {
    int usr_command = -1;
    while (usr_command != 0) {
        print_options();
        std::cin >> usr_command;
        if (usr_command == 1) {
            this->remove();
        } else if (usr_command == 2) {
            this->print_schools();
        } else if (usr_command == 3) {
            this->mark();
        } else {
            std::cout << "Err. Invalid option\n";
        }
    }
}

void UI::remove() {
    print_schools();
    std::string name;
    double lon, lat;
    std::cout << "Enter school name:";
    std::cin >> name;

    std::cout << "Enter longitude:";
    std::cin >> lon;

    std::cout << "Enter latitude:";
    std::cin >> lat;

    int res = this->service.remove(name, lon, lat);
    if (res == 1) {
        std::cout << "School removed successfully.\n";
    } else if (res == 0) {
        std::cout << "No such school exists.\n";
    }
}

UI::UI(Service serv) {
    this->service = std::move(serv);
}

void UI::print_options() {
    std::cout << "1. Remove a school\n"
                 "2. Show all schools\n"
                 "3. Given a date, mark all schools visited before that date.\n"
                 "0. Exit\n";
}

void UI::print_schools() {
    std::vector<School> v = this->service.get_sorted();

    int index = 0;
    for (auto &i : v) {
        std::cout << index++ << ". School " << i.name << "(" << i.lat << ", " << i.lon << ") is to be visited on the date " << i.day
                    << "." << i.mon << "." << i.year;
        if (i.visited) {
            std::cout << " was visited.\n";
        } else {
            std::cout << " was not visited.\n";
        }
    }
    std::cout << std::endl;
}

void UI::mark() {
    int day, mon, year;

    std::cout << "Enter day:";
    std::cin >> day;

    std::cout << "Enter month:";
    std::cin >> mon;

    std::cout << "Enter year:";
    std::cin >> year;

    std::vector<School> v = service.mark(day, mon, year);

    int index = 0;
    for (auto &i : v) {
        std::cout << index++ << ". School " << i.name << "(" << i.lat << ", " << i.lon << ") is to be visited on the date " << i.day
                  << "." << i.mon << "." << i.year;
        if (i.visited) {
            std::cout << " was visited.\n";
        } else {
            std::cout << " was not visited.\n";
        }
    }
    std::cout << std::endl;
}
