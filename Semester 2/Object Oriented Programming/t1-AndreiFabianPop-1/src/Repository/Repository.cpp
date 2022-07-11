//
// Created by andre on 07/04/2022.
//

#include "Repository.h"

void Repository::add(const School& s) {
    this->v.push_back(s);
}

int Repository::remove(const std::string& name, double lon, double lat) {
    for (auto & i : this->v) {
        if (i.name == name && i.lon == lon && i.lat == lat) {
            std::swap(i, this->v.back());
            this->v.pop_back();
            return 1;
        }
    }
    return 0;
}

std::vector<School> Repository::get_all() {
    return this->v;
}
