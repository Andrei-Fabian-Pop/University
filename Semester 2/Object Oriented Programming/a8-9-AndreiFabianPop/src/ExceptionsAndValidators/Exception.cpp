//
// Created by andre on 16/04/2022.
//

#include "Exception.h"

#include <utility>

RepositoryException::RepositoryException() : exception {} {}

RepositoryException::RepositoryException(std::string msg) : message(std::move(msg)) {}

const char *RepositoryException::what() { return this->message.c_str(); }


const char *DuplicateException::what() {
    return "There is another instance with the same keys!";
}

const char *IncorrectPosition::what() {
    return "The position is incorrect!";
}

FileException::FileException(std::string msg) {
    this->message = std::move(msg);
}

const char *FileException::what() {
    return this->message.c_str();
}
