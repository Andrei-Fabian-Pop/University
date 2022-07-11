//
// Created by andre on 19/03/2022.
//

#include "Service.h"

#include <utility>

Service::Service(const Repository<Tutorial>& repository, WatchList<Tutorial>* wl, std::string databaseType) : mainDatabase(repository) {
    this->mainDatabase = repository;
    this->watchList = wl;
    this->databaseType = std::move(databaseType);
}

int Service::add(std::string title, std::string presenter, int duration_minutes, int duration_seconds, int likes, std::string link) {
    Tutorial tutorial(std::move(title), std::move(presenter), duration_minutes, duration_seconds, likes, std::move(link));
    Validator::validateTutorial(tutorial);
    Tutorial *tutorial_p = &tutorial;

    int result = this->mainDatabase.add(*tutorial_p);
    return result;
}

int Service::remove(int index) {
    if (!mainDatabase.valid_index(index)) {
        throw IncorrectPosition();
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

WatchList<Tutorial>* Service::get_by_presenter(const std::string& presenter) {
    std::vector<Tutorial> tut;
    if (presenter.empty()) {
//        return this->mainDatabase.get_all();
        tut = this->mainDatabase.get_all();
    } else {
        Repository<Tutorial> presenterTutorials;
        for (int i = 0; i < this->mainDatabase.getSize(); ++i) {
            if (this->mainDatabase[i].get_presenter() == presenter) {
                tut.push_back(this->mainDatabase[i]);
            }
        }
//        return presenterTutorials.get_all();
    }

    WatchList<Tutorial> *res;
    if (this->databaseType == "csv") {
        res = new CSV_WatchList<Tutorial>("watchlist.txt");
    } else {
        res = new HTML_WatchList<Tutorial>("watchlist.txt");
    }
    res->setWatchList(tut);
    return res;
}

int Service::add_to_playlist(const Tutorial& tutorial) {
    const Tutorial *tutorial_p = &tutorial;

    return this->watchList->add(*tutorial_p);
}

std::vector<Tutorial> Service::get_watchList() {
    return this->watchList->getAll();
}

int Service::remove_from_playlist(int index) {
    if (index < 0 || index >= watchList->getSize()) {
        return 0;
    } else {
        watchList->removeByPos(index);
        return 1;
    }
}

void Service::like(int index) {
    this->mainDatabase[index].set_likes(this->mainDatabase[index].get_likes() + 1);
}

int Service::get_index(const std::string&  title, const std::string&  presenter, const std::string&  link) {
    return this->mainDatabase.get_index(title, presenter, link);
}

void Service::saveWatchlist() {
    this->watchList->saveToFile();
}

void Service::openWatchlist() {
    this->watchList->openApp();
}

int Service::updateFull(int index, std::string title, std::string presenter, int duration_minutes, int duration_seconds, int likes, std::string link) {
    this->mainDatabase[index].set_title(std::move(title));
    this->mainDatabase[index].set_presenter(std::move(presenter));
    this->mainDatabase[index].set_duration_minutes(duration_minutes);
    this->mainDatabase[index].set_duration_seconds(duration_seconds);
    this->mainDatabase[index].set_likes(likes);
    this->mainDatabase[index].set_link(std::move(link));

    return 1;
}

Service::~Service() = default;
