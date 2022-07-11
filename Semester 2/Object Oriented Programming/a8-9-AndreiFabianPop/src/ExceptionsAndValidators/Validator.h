//
// Created by andre on 16/04/2022.
//

#ifndef A8_9_ANDREIFABIANPOP_VALIDATOR_H
#define A8_9_ANDREIFABIANPOP_VALIDATOR_H

#include "../Domain/Tutorial.h"
#include <exception>
#include <vector>
#include <regex>

class Validator {
public:
    explicit Validator();
    ~Validator();

    static void validateTutorial(const Tutorial& tutorial);
};

class TutorialException : public std::exception {
private:
    std::vector<std::string> errors;

public:
    explicit TutorialException(std::vector<std::string> _errors);
    std::vector<std::string> getErrors() const;
};

#endif //A8_9_ANDREIFABIANPOP_VALIDATOR_H
