//
// Created by andrew on 12/06/22.
//

#include "User.h"

User::User(const std::string &name) : name(name) {}

const std::string &User::getName() const {
    return name;
}

void User::setName(const std::string &name) {
    User::name = name;
}
