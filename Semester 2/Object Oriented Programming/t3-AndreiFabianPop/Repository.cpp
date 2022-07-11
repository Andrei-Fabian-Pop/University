//
// Created by andrew on 26/05/22.
//

#include <iostream>
#include "Repository.h"

void Repository::read() {
    std::ifstream file("textfile.txt");
    if (!file.is_open()) {
        std::cerr << "File did not open\n";
    }

    std::string string;
    while (std::getline(file, string)) {
        std::vector<std::string> keywords, doc = tokenize(string, '|');
        Document document(doc[0], tokenize(doc[1], ','), doc[2]);
        this->documents.push_back(document);
    }

    std::sort(this->documents.begin(), this->documents.end(), [&](const Document& document1, const Document& document2) {
        return (document1.getContent().size() <= document2.getContent().size());
    });

    file.close();
}

std::vector<std::string> Repository::tokenize(const std::string& string, char delimiter) {
    std::stringstream ss(string);
    std::vector<std::string> result;
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        result.push_back(part);
    }

    return result;
}
