//
// Created by andre on 03/03/2022.
//
// Assignment 2: Pharmacy
//
#include <crtdbg.h>

#include "domain/medicine.h"
#include "repository/repository.h"
#include "service/service.h"
#include "ui/ui.h"
#include "tests/tests.h"

void add_10_entries(Medicine_array **med_array) {
    Service_medicine__add(&(*med_array), "Parasinus", 30, 7, 13);
    Service_medicine__add(&(*med_array), "Nurofen", 40, 56, 34);
    Service_medicine__add(&(*med_array), "Paracetamol", 50, 45, 36);
    Service_medicine__add(&(*med_array), "Algocalmin", 88, 78, 45);
    Service_medicine__add(&(*med_array), "Aspenter", 42, 3, 65);

    Service_medicine__add(&(*med_array), "Antinevralgic", 76, 99, 76);
    Service_medicine__add(&(*med_array), "Detralex", 34, 36, 21);
    Service_medicine__add(&(*med_array), "Tertensif", 45, 55, 43);
    Service_medicine__add(&(*med_array), "Atoris", 43, 78, 54);
    Service_medicine__add(&(*med_array), "Sortis", 76, 2, 68);
}

int main() {
    test_all();

    Medicine_array *med_arr = Medicine_array__create(0);
    add_10_entries(&med_arr);

    UI__start(&med_arr);

    _CrtDumpMemoryLeaks();

    return 0;
}