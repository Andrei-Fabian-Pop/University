//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_USER_H
#define E916_ANDREIFABIANPOP_1_USER_H

#include <string>

class User {
private:
    std::string name;
public:
    explicit User(const std::string &name);

    [[nodiscard]] const std::string &getName() const;

    void setName(const std::string &name);
};


#endif //E916_ANDREIFABIANPOP_1_USER_H
