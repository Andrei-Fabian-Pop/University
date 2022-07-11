//
// Created by andre on 19/03/2022.
//

#include "UI/UI.h"
//#include "DynamicVector/DynamicVector.h"
#include "Repository/Repository.h"
#include "Tests/Tests.h"

void add_10_entries(Service& service) {
    service.add("Title1", "Presenter1", 11, 11, 0, "www.link1.com");
    service.add("Title2", "Presenter2", 12, 12, 0, "www.link2.com");
    service.add("Title3", "Presenter3", 13, 13, 0, "www.link3.com");
    service.add("Title4", "Presenter4", 14, 14, 0, "www.link4.com");
    service.add("Title5", "Presenter5", 15, 15, 0, "www.link5.com");
    service.add("Title6", "Presenter6", 16, 16, 0, "www.link6.com");
    service.add("Title7", "Presenter7", 17, 17, 0, "www.link7.com");
    service.add("Title8", "Presenter8", 18, 18, 0, "www.link8.com");
    service.add("Title9", "Presenter9", 19, 19, 0, "www.link9.com");
    service.add("Title10", "Presenter10", 20, 20, 0, "www.link10.com");
}

int main() {

    Tests::testDomain();
    Tests::testRepository();
    Tests::testService();
    std::cout << "All tests passed...\n";

    Repository<Tutorial> mainDatabase;
    Service service(mainDatabase);
    add_10_entries(service);

    std::cout << "Enter the mode you want(1. Administrator, 2. Client):\n";
    int user_command = UI::get_user_input();
    if (user_command == 1) {
        // Admin mode start
        Admin admin(service);
        admin.start();

    } else if (user_command == 2) {
        // Client mode start
        Client client(service);
        client.start();
    } else {
        std::cout << "Invalid command. Program terminating.\n";
    }

    return 0;
}