//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_USERLIST_H
#define E916_ANDREIFABIANPOP_1_USERLIST_H

#include <vector>
#include <string>

#include "User.h"

class UserList {
private:
    std::vector<User> list;
public:
    explicit UserList() = default;
    void add(const User& u) { this->list.push_back(u); }
    std::vector<User> getAll() { return this->list; }
};


#endif //E916_ANDREIFABIANPOP_1_USERLIST_H
