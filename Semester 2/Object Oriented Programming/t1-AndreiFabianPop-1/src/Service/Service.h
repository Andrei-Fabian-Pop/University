//
// Created by andre on 07/04/2022.
//

#ifndef T1_ANDREIFABIANPOP_1_SERVICE_H
#define T1_ANDREIFABIANPOP_1_SERVICE_H

#include "../Repository/Repository.h"
#include <algorithm>

class Service {
private:
    Repository repository;
public:
    explicit Service(Repository repo);
    explicit Service();

    static bool sortF(const School& i, const School& j);

    int add(const std::string& name, double lon, double lat, int day, int mon, int year, bool visited);
    int remove(const std::string& name, double lon, double lat);
    // Function iterates through the vector if it finds a match it swaps it with the last element and pops it

    std::vector<School> get_sorted();

    std::vector<School> mark(int day, int mon, int year);
    // Function gets all schools and filters them by checking the date and then adds the ones that are after to a vector
    // that is returned or marks them as visited
};


#endif //T1_ANDREIFABIANPOP_1_SERVICE_H
