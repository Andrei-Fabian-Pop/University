//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_ANSWER_H
#define E916_ANDREIFABIANPOP_1_ANSWER_H

#include <string>

class Answer {
private:
    int id;
    int qid;
    std::string userName;
    std::string text;
    int nrVotes;
public:
    Answer(int id, int qid, const std::string &userName, const std::string &text, int nrVotes);

    int getId() const;

    void setId(int id);

    int getQid() const;

    void setQid(int qid);

    const std::string &getUserName() const;

    void setUserName(const std::string &userName);

    const std::string &getText() const;

    void setText(const std::string &text);

    int getNrVotes() const;

    void setNrVotes(int _nrVotes);
};


#endif //E916_ANDREIFABIANPOP_1_ANSWER_H
