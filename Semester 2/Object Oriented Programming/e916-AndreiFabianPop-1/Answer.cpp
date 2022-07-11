//
// Created by andrew on 12/06/22.
//

#include "Answer.h"

Answer::Answer(int id, int qid, const std::string &userName, const std::string &text, int nrVotes) : id(id), qid(qid),
                                                                                                     userName(userName),
                                                                                                     text(text),
                                                                                                     nrVotes(nrVotes) {}

int Answer::getId() const {
    return id;
}

void Answer::setId(int id) {
    Answer::id = id;
}

int Answer::getQid() const {
    return qid;
}

void Answer::setQid(int qid) {
    Answer::qid = qid;
}

const std::string &Answer::getUserName() const {
    return userName;
}

void Answer::setUserName(const std::string &userName) {
    Answer::userName = userName;
}

const std::string &Answer::getText() const {
    return text;
}

void Answer::setText(const std::string &text) {
    Answer::text = text;
}

int Answer::getNrVotes() const {
    return nrVotes;
}

void Answer::setNrVotes(int _nrVotes) {
    this->nrVotes = _nrVotes;
}
