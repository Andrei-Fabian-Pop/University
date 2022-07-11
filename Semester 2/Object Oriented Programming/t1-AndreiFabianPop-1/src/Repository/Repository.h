//
// Created by andre on 07/04/2022.
//

#ifndef T1_ANDREIFABIANPOP_1_REPOSITORY_H
#define T1_ANDREIFABIANPOP_1_REPOSITORY_H

#include <vector>
#include "../domain/School.h"

class Repository {
private:
    std::vector<School> v;
public:
    void add(const School& s);
    int remove(const std::string& name, double lon, double lat);
    std::vector<School> get_all();
};


#endif //T1_ANDREIFABIANPOP_1_REPOSITORY_H
