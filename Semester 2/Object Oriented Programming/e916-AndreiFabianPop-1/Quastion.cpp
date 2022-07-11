//
// Created by andrew on 12/06/22.
//

#include "Quastion.h"

Question::Question(int id, const std::string &text, const std::string &userName) : id(id), text(text),
                                                                                   userName(userName) {}

int Question::getId() const {
    return id;
}

void Question::setId(int id) {
    Question::id = id;
}

const std::string &Question::getText() const {
    return text;
}

void Question::setText(const std::string &text) {
    Question::text = text;
}

const std::string &Question::getUserName() const {
    return userName;
}

void Question::setUserName(const std::string &userName) {
    Question::userName = userName;
}

std::string Question::toString() const {
    return std::to_string(this->getId()) + " " + this->getText() + ": " + this->getUserName();
}
