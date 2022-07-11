//
// Created by andre on 19/03/2022.
//

#include "Tutorial.h"
#include <utility>


Tutorial::Tutorial(std::string title, std::string presenter, int duration_minutes, int duration_seconds,
                   int likes, std::string link) {
    this->title = std::move(title);
    this->presenter = std::move(presenter);
    this->link = std::move(link);

    this->duration_minutes = duration_minutes;
    this->duration_seconds = duration_seconds;
    this->likes = likes;
}

Tutorial::Tutorial() {
    this->title = "";
    this->presenter = "";
    this->link = "";

    this->duration_minutes = 0;
    this->duration_seconds = 0;
    this->likes = 0;
}

std::string Tutorial::get_title() const {
    return this->title;
}

void Tutorial::set_title(std::string new_title) {
    this->title = std::move(new_title);
}

std::string Tutorial::get_presenter() const {
    return this->presenter;
}

void Tutorial::set_presenter(std::string new_presenter) {
    this->presenter = std::move(new_presenter);
}

int Tutorial::get_duration_minutes() const {
    return this->duration_minutes;
}

void Tutorial::set_duration_minutes(int minutes) {
    this->duration_minutes = minutes;
}

int Tutorial::get_duration_seconds() const {
    return this->duration_seconds;
}

void Tutorial::set_duration_seconds(int seconds) {
    this->duration_seconds = seconds;
}

int Tutorial::get_likes() const {
    return this->likes;
}

void Tutorial::set_likes(int new_likes) {
    this->likes = new_likes;
}

std::string Tutorial::get_link() const {
    return this->link;
}

void Tutorial::set_link(std::string new_link) {
    this->link = std::move(new_link);
}

Tutorial::~Tutorial() = default;

Tutorial::Tutorial(const Tutorial &t) {
    this->title = t.title;
    this->presenter = t.presenter;
    this->link = t.link;

    this->duration_minutes = t.duration_minutes;
    this->duration_seconds = t.duration_seconds;
    this->likes = t.likes;
}

void Tutorial::executeLink() {
    std::string command = "firefox " + this->link;
    system(command.c_str());
}

std::istream &operator>>(std::istream &istream, Tutorial &tutorial) {
    if (istream.eof()) {
        istream.setstate(std::ios_base::failbit);
    } else {
        std::string string;
        std::vector<std::string> output;
        std::getline(istream, string);
        if (!string.empty()) {
            output = Tutorial::tokenize(string, ',');
            if (output.size() != 6) {
                return istream;
            }
            tutorial.title = output[0];
            tutorial.presenter = output[1];
            tutorial.duration_minutes = stoi(output[2]);
            tutorial.duration_seconds = stoi(output[3]);
            tutorial.likes = stoi(output[4]);
            tutorial.link = output[5];
        } else {
            tutorial.likes = -1;
        }
    }

    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Tutorial &tutorial) {
    ostream << tutorial.title << "," <<
            tutorial.presenter << "," <<
            tutorial.duration_minutes << "," <<
            tutorial.duration_seconds << "," <<
            tutorial.likes << "," <<
            tutorial.link << "\n";
    return ostream;
}

std::vector<std::string> Tutorial::tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}
