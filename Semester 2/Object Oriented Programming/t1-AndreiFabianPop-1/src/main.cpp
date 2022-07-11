//
// Created by andre on 07/04/2022.
//

#include "Repository/Repository.h"
#include "Service/Service.h"
#include "UI/UI.h"
#include <cassert>

int main() {
    Repository repository;

    // add here
    repository.add(School("N2", 11, 11, 15, 4, 2022, false));
    repository.add(School("N1", 12, 12, 15, 2, 2022, false));
    repository.add(School("N3", 13, 13, 15, 3, 2022, true));
    repository.add(School("N4", 14, 14, 15, 5, 2022, false));
    repository.add(School("N5", 15, 15, 15, 6, 2022, true));

    Service service(repository);
    UI ui(service);

    // tests
    repository.add(School("test", 10, 10, 15, 6, 2022, true));
    repository.remove("test", 10, 10);
    assert(repository.get_all().back().name != "test");
    assert(repository.get_all().back().lon != 10);
    assert(repository.get_all().back().lat != 10);


    ui.start();

    return 0;
}