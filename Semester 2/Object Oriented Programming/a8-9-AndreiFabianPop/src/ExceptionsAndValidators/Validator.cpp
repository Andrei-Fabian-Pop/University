//
// Created by andre on 16/04/2022.
//

#include "Validator.h"

#include <utility>

Validator::Validator() = default;

Validator::~Validator() = default;

void Validator::validateTutorial(const Tutorial &tutorial) {
    std::vector<std::string> errors;
    std::regex link_regex(R"([(http(s)?):\/\/(www\.)?a-zA-Z0-9@:%._\+~#=]{2,256}\.[a-z]{2,6}\b([-a-zA-Z0-9@:%_\+.~#?&//=]*))",
                          std::regex_constants::icase);
    if (tutorial.get_title().empty())
        errors.emplace_back("The title cannot be empty!\n");
    if (tutorial.get_presenter().empty())
        errors.emplace_back("The presenter cannot be empty!\n");
    if (tutorial.get_duration_minutes() < 0)
        errors.emplace_back("The duration in minutes cannot be negative!\n");
    if (tutorial.get_duration_seconds() < 0)
        errors.emplace_back("The duration in seconds cannot be negative!\n");
    if (tutorial.get_duration_seconds() >= 60)
        errors.emplace_back("The duration in seconds cannot be above 60!\n");
    if (tutorial.get_likes() < 0)
        errors.emplace_back("The number of likes cannot be below 0!\n");
    if (std::regex_match(tutorial.get_link(), link_regex) == 0)
        errors.emplace_back("Invalid link!\n");

    if (!errors.empty())
        throw TutorialException(errors);
}

TutorialException::TutorialException(std::vector<std::string> _errors) {
    this->errors = std::move(_errors);
}

std::vector<std::string> TutorialException::getErrors() const {
    return this->errors;
}
