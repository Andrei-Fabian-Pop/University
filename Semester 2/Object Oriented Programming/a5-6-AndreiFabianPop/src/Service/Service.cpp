//
// Created by andre on 19/03/2022.
//

#include "Service.h"

#include <utility>

Service::Service(const Repository<Tutorial>& repository) : mainDatabase(repository) {
    this->mainDatabase = repository;
    this->watchList = Repository<Tutorial>();
}

int Service::add(std::string title, std::string presenter, int duration_minutes, int duration_seconds, int likes, std::string link) {
    if (duration_minutes < 0) {
        return -1;
    }
    if (duration_seconds < 0 || duration_seconds >= 60) {
        return -2;
    }
    if (likes < 0) {
        return -3;
    }

    Tutorial tutorial(std::move(title), std::move(presenter), duration_minutes, duration_seconds, likes, std::move(link));
    Tutorial *tutorial_p = &tutorial;

    int result = this->mainDatabase.add(*tutorial_p);
    return result;
}

int Service::remove(int index) {
    if (!mainDatabase.valid_index(index)) {
        return 0;
    } else {
        mainDatabase.remove(index);
        return 1;
    }
}

Repository<Tutorial> Service::get_all() const {
    return mainDatabase;
}

int Service::update(int index, int field_index, std::string string_field, int int_field) {
    if (field_index == 0) {
        mainDatabase[index].set_title(std::move(string_field));
    } else if (field_index == 1) {
        mainDatabase[index].set_presenter(std::move(string_field));
    } else if (field_index == 2) {
        mainDatabase[index].set_duration_minutes(int_field);
    } else if (field_index == 3) {
        mainDatabase[index].set_duration_seconds(int_field);
    } else if (field_index == 4) {
        mainDatabase[index].set_likes(int_field);
    } else if (field_index == 5) {
        mainDatabase[index].set_link(string_field);
    }

    return 1;
}

bool Service::valid_index(int index) const {
    return mainDatabase.valid_index(index);
}

std::vector<Tutorial> Service::get_by_presenter(const std::string& presenter) {
    if (presenter.empty()) {
        return this->mainDatabase.get_all();
    } else {
        Repository<Tutorial> presenterTutorials;
        for (int i = 0; i < this->mainDatabase.getSize(); ++i) {
            if (this->mainDatabase[i].get_presenter() == presenter) {
                presenterTutorials.add(this->mainDatabase[i]);
            }
        }

        return presenterTutorials.get_all();
    }
}

int Service::add_to_playlist(const Tutorial& tutorial) {
    const Tutorial *tutorial_p = &tutorial;

    return this->watchList.add(*tutorial_p);
}

Repository<Tutorial> Service::get_watchList() const {
    return this->watchList;
}

int Service::remove_from_playlist(int index) {
    if (!watchList.valid_index(index)) {
        return 0;
    } else {
        watchList.remove(index);
        return 1;
    }
}

void Service::like(int index) {
    this->mainDatabase[index].set_likes(this->mainDatabase[index].get_likes() + 1);
}

Service::~Service() = default;
