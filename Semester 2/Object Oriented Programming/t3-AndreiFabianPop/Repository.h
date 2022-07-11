//
// Created by andrew on 26/05/22.
//

#ifndef T3_ANDREIFABIANPOP_REPOSITORY_H
#define T3_ANDREIFABIANPOP_REPOSITORY_H

#include "Document.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class Repository {
private:
    std::vector<Document> documents;
public:
    Repository() = default;

    void read();
    static std::vector<std::string> tokenize(const std::string& string, char delimiter);

    std::vector<Document> getAll() { return this->documents; }
};


#endif //T3_ANDREIFABIANPOP_REPOSITORY_H
