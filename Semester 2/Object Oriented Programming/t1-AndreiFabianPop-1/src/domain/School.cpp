//
// Created by andre on 07/04/2022.
//

#include "School.h"

#include <utility>

School::School(std::string name, double lon, double lat, int day, int mon, int year, bool b) {
    this->name = std::move(name);
    this->lon = lon;
    this->lat = lat;
    this->day = day;
    this->mon = mon;
    this->year = year;
    this->visited = b;
}
