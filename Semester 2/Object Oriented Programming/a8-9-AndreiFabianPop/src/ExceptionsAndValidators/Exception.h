//
// Created by andre on 16/04/2022.
//

#ifndef A8_9_ANDREIFABIANPOP_EXCEPTION_H
#define A8_9_ANDREIFABIANPOP_EXCEPTION_H

#include <string>
#include <exception>

class RepositoryException : std::exception {
protected:
    std::string message;

public:
    explicit RepositoryException();
    explicit RepositoryException(std::string msg);
    ~RepositoryException() override = default;
    virtual const char* what();
};

class DuplicateException : RepositoryException {
public:
    const char* what() override;
};

class IncorrectPosition : RepositoryException {
public:
    const char* what() override;
};

class FileException : std::exception {
protected:
    std::string message;

public:
    explicit FileException(std::string msg);
    virtual const char* what();
};

#endif //A8_9_ANDREIFABIANPOP_EXCEPTION_H
