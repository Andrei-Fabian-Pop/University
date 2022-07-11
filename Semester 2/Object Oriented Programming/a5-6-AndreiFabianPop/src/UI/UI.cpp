//
// Created by andre on 19/03/2022.
//

#include "UI.h"

Admin::Admin(const Service &service) : UI(service) {

}

void Admin::start() {
    int admin_command = -1;
    while (admin_command != 0) {
        print_options();
        admin_command = get_user_input();
        if (admin_command < 0 || admin_command > MAX_OPTION) {
            std::cout << "This command index does not exist, please enter a valid command." << std::endl;
            admin_command = -1;
        } else {
            if (admin_command == 1) {
                add();
            } else if (admin_command == 2) {
                remove();
            } else if (admin_command == 3) {
                update();
            } else if (admin_command == 4) {
                print_all();
            }
        }
    }
}

void Admin::print_options() {
    std::cout << "Administrator options:" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Add tutorial" << std::endl;
    std::cout << "2. Delete tutorial" << std::endl;
    std::cout << "3. Update tutorial" << std::endl;
    std::cout << "4. See all tutorials" << std::endl;
}

void Admin::add() {
    std::string title, presenter, link;
    int duration_minutes, duration_seconds, likes;
    std::cin.get();
    std::cout << "Enter the tutorial title(max 100 characters):" << std::endl;
    std::cin >> title;

    std::cout << "Enter the tutorial presenter(max 100 characters):\n";
    std::cin >> presenter;

    std::cout << "Enter the tutorial duration in minutes:\n";
    duration_minutes = get_user_input();

    std::cout << "Enter the tutorial duration in seconds:\n";
    duration_seconds = get_user_input();

    std::cout << "Enter the tutorial likes:\n";
    likes = get_user_input();

    std::cin.get();
    std::cout << "Enter the tutorial link(max 100 characters):\n";
    std::cin >> link;

    int result = service.add(title, presenter, duration_minutes, duration_seconds, likes, link);
    if (result == 1) {
        std::cout << "Tutorial added successfully.\n";
    } else if (result == 0) {
        std::cout << "This tutorial already exists, no tutorial was added.\n";
    } else if (result == -1) {
        std::cout << "The duration in minutes is incorrect, no tutorial was created.\n";
    } else if (result == -2) {
        std::cout << "The duration in seconds is incorrect, no tutorial was created.\n";
    } else if (result == -3) {
        std::cout << "The number of likes is incorrect, no tutorial was created.\n";
    }
}

void Admin::remove() {
    std::cout << "The tutorial entries are:\n";
    print_all();
    std::cout << "Choose the entry that you want ot remove: ";
    int index = get_user_input();

    int result = service.remove(index);
    if (result == 1) {
        std::cout << "Tutorial removed successfully" << std::endl;
    } else if (result == 0) {
        std::cout << "No tutorial with this index was found" << std::endl;
    }
}

void Admin::update() {
    std::cout << "The tutorial entries are:\n";
    print_all();
    std::cout << "Choose the entry that you want ot remove: ";
    int index = get_user_input();
    if (!service.valid_index(index)) {
        std::cout << "Index is not valid, please enter a valid one." << std::endl;
    } else {
        std::cout << "Entry selected. What is the field you want to update?" << std::endl;
        std::cout << "0. Title\n1. Presenter\n2. Duration in minutes\n3. Duration in seconds\n4. Number of likes\n5. Link\n";
        int field_index = get_user_input();
        if (field_index >= 0 && field_index < 6) {
            if (field_index < 2 || field_index == 5) {
                std::cout << "Enter the new string:" << std::endl;
                std::string field;
                std::cin.get();
                std::cin >> field;
                service.update(index, field_index, field, -1);
            } else {
                std::cout << "Enter the new integer:" << std::endl;
                int field;
                std::cin >> field;
                service.update(index, field_index, "", field);
            }
        } else {
            std::cout << "Invalid field. No changes were made." << std::endl;
        }
    }
}

void Admin::print_all() {
    std::vector<Tutorial> arr = service.get_all().get_all();
    int count = 0;
    std::for_each(arr.begin(), arr.end(), [&](const Tutorial& tutorial){
            std::cout << count++ << ". " << tutorial.get_title() << ", by " << tutorial.get_presenter() <<
            " with a length of " << tutorial.get_duration_minutes() << ":" << tutorial.get_duration_seconds() <<
            " and " << tutorial.get_likes() << " likes has the link: " << tutorial.get_link() << "." << std::endl;
        }
    );
}

Admin::~Admin() = default;

UI::UI(const Service &service) : service(Repository<Tutorial>()) {
    this->service = service;
}

int UI::get_user_input() {
    int user_input;
    bool is_correct;
    std::cin.exceptions(std::istream::failbit);
    do {
        try {
            std::cout << "> ";
            std::cin >> user_input;
            std::cin.clear();
            is_correct = true;
        } catch (std::ios_base::failure &failure) {
            is_correct = false;
            std::cout << "This input is invalid, please enter an integer" << std::endl;
            std::cin.clear();
            std::cin.get();
        }
    } while (!is_correct);

    return user_input;
}

UI::~UI() = default;

Client::Client(const Service &service) : UI(service) {

}

void Client::start() {
    int client_command = -1;
    while (client_command != 0) {
        print_options();
        client_command = get_user_input();
        if (client_command < 0 || client_command > MAX_OPTION) {
            std::cout << "This command index does not exist, please enter a valid command." << std::endl;
            client_command = -1;
        } else {
            if (client_command == 1) {
                print_by_presenter();
            } else if (client_command == 2) {
                delete_from_playlist();
            } else if (client_command == 3) {
                print_watchlist();
            }
        }
    }
}

void Client::print_options() {
    std::cout << "Client options:" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. See and play tutorials of a given presenter" << std::endl;
    std::cout << "2. Delete from watchlist" << std::endl;
    std::cout << "3. See watchlist" << std::endl;
}

void Client::print_by_presenter() {
    std::cout << "Enter the presenter name(or leave empty):";
    std::string presenter;
    char pres[101];
    std::cin.get();
    std::cin.getline(pres, 101);
    presenter = pres;

    std::vector<Tutorial> arr = service.get_by_presenter(presenter);
    int count = 0;
    std::for_each(arr.begin(), arr.end(), [&](const Tutorial& tutorial){
        std::cout << count++ << ". " << tutorial.get_title() << ", by " << tutorial.get_presenter() <<
        " with a length of " << tutorial.get_duration_minutes() << ":" << tutorial.get_duration_seconds() <<
        " and " << tutorial.get_likes() << " likes has the link: " << tutorial.get_link() << "." << std::endl;
    });

    int client_option, index = 0;
    std::cout << "Playing:" << arr[index].get_title() << ", by " << arr[index].get_presenter() <<
                " with a length of " << arr[index].get_duration_minutes() << ":" << arr[index].get_duration_seconds() <<
                " and " << arr[index].get_likes() << " likes has the link: " << arr[index].get_link() << "." << std::endl;
    open_in_browser(arr[index]);
    bool liked = false;
    while (true) {
        std::cout << "Tutorial options:\n"
                     "1. Add to playlist\n"
                     "2. Like\n"
                     "3. Next\n"
                     "0. Stop\n";
        client_option = get_user_input();
        if (client_option == 1) {
            int result = service.add_to_playlist(arr[index]);
            if (result == 1) {
                std::cout << "Tutorial successfully added.\n";
            } else if (result == 0) {
                std::cout << "Tutorial is already in the watchlist.\n";
            }
        } else if (client_option == 2) {
            if (!liked) {
                liked = true;
                service.like(index);
                arr[index].set_likes(arr[index].get_likes() + 1);
                std::cout << "Tutorial liked successfully.\n";
            } else {
                std::cout << "Tutorial already liked.\n";
            }
        } else if (client_option == 3) {
            liked = false;
            ++index;
            if (index >= arr.size()) {
                index = 0;
            }
            open_in_browser(arr[index]);
            std::cout << "Playing:" << arr[index].get_title() << ", by " << arr[index].get_presenter() <<
                      " with a length of " << arr[index].get_duration_minutes() << ":" << arr[index].get_duration_seconds() <<
                      " and " << arr[index].get_likes() << " likes has the link: " << arr[index].get_link() << "." << std::endl;
        } else if (client_option == 0) {
            break;
        } else { std::cout << "Invalid input\n"; }
    }
}

void Client::delete_from_playlist() {
    print_watchlist();

    std::cout << "Enter the index you want to delete.\n";
    int index = get_user_input();
    int result = service.remove_from_playlist(index);
    if (result == 0) {
        std::cout << "Invalid index.\n";
        return;
    } else {
        std::cout << "Tutorial removed successfully.\n";
    }

}

void Client::open_in_browser(const Tutorial& tutorial) {
    ShellExecuteA(nullptr,
                  nullptr,
                  "chrome.exe",
                  tutorial.get_link().c_str(),
                  nullptr,
                  SW_SHOWMAXIMIZED);
}

void Client::print_watchlist() {
    std::vector<Tutorial> watchlist = service.get_watchList().get_all();
    int count = 0;
    std::for_each(watchlist.begin(), watchlist.end(), [&](const Tutorial& tutorial){
        std::cout << count++ << ". " << tutorial.get_title() << ", by " << tutorial.get_presenter() <<
        " with a length of " << tutorial.get_duration_minutes() << ":" << tutorial.get_duration_seconds() <<
        " and " << tutorial.get_likes() << " likes has the link: " << tutorial.get_link() << "." << std::endl;
    });
}

Client::~Client() = default;