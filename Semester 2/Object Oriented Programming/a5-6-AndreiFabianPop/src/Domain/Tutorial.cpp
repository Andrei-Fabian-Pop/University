//
// Created by andre on 19/03/2022.
//

#include "Tutorial.h"

#include <utility>


Tutorial::Tutorial(std::string title, std::string presenter, unsigned int duration_minutes, unsigned int duration_seconds,
                   unsigned int likes, std::string link) {
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

unsigned int Tutorial::get_duration_minutes() const {
    return this->duration_minutes;
}

void Tutorial::set_duration_minutes(unsigned int minutes) {
    this->duration_minutes = minutes;
}

unsigned int Tutorial::get_duration_seconds() const {
    return this->duration_seconds;
}

void Tutorial::set_duration_seconds(unsigned int seconds) {
    this->duration_seconds = seconds;
}

unsigned int Tutorial::get_likes() const {
    return this->likes;
}

void Tutorial::set_likes(unsigned int new_likes) {
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
