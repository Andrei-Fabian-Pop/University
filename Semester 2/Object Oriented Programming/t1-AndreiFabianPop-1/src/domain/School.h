//
// Created by andre on 07/04/2022.
//

#ifndef T1_ANDREIFABIANPOP_1_SCHOOL_H
#define T1_ANDREIFABIANPOP_1_SCHOOL_H

#include <string>

struct School {
    School(std::string name, double lon, double lat, int day, int mon, int year, bool b);

    std::string name;
    double lon;
    double lat;
    int day, mon, year;
    bool visited;
};

//class School {
//private:
//
//};


#endif //T1_ANDREIFABIANPOP_1_SCHOOL_H
