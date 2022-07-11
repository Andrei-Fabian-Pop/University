//
// Created by andre on 07/04/2022.
//

#include "Service.h"

#include <utility>

Service::Service(Repository repo) {
    this->repository = std::move(repo);
}

int Service::add(const std::string& name, double lon, double lat, int day, int mon, int year, bool visited) {

    return 0;
}

int Service::remove(const std::string& name, double lon, double lat) {
    return this->repository.remove(name, lon, lat);
}

std::vector<School> Service::get_sorted() {
    std::vector<School> v = repository.get_all();
    std::sort(v.begin(), v.end(), Service::sortF);
    return v;
}

bool Service::sortF(const School& i, const School& j) {
    return (i.name < j.name);
}

std::vector<School> Service::mark(int day, int mon, int year) {
    std::vector<School> v = repository.get_all();
    std::vector<School> vvis;

    for (auto &i : v) {
        bool vis = false;
        if (i.year < year) {
            i.visited = true;
            vis = true;
        } else if (i.year == year) {
            if (i.mon < mon) {
                i.visited = true;
                vis = true;
            } else if (i.mon == mon) {
                if (i.day < day) {
                    i.visited = true;
                    vis = true;
                }
            }
        }

        if (!vis) {
            vvis.push_back(i);
        }
    }

    return vvis;
}

Service::Service() = default;
