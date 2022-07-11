//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_QUASTION_H
#define E916_ANDREIFABIANPOP_1_QUASTION_H

#include <string>

class Question {
private:
    int id;
    std::string text;
    std::string userName;
public:
    Question(int id, const std::string &text, const std::string &userName);
    Question() = default;

    int getId() const;

    void setId(int id);

    const std::string &getText() const;

    void setText(const std::string &text);

    const std::string &getUserName() const;

    void setUserName(const std::string &userName);

    std::string toString() const;
};


#endif //E916_ANDREIFABIANPOP_1_QUASTION_H
