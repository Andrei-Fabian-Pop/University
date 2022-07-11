//
// Created by andre on 08/03/2022.
//

#include "tests.h"

void test_all() {
    test_domain();
    test_repository();
    test_service();
}

void test_domain() {
    printf("Starting domain tests...\n");
    Medicine *med = Medicine__create("test1", (float)(66.88), 12, 66);

    // test init
    assert(strcmp(med->name, "test1") == 0);
    assert(med->concentration == (float)(66.88));
    assert(med->quantity == 12);
    assert(med->price == 66);

    Medicine__destroy(med);

    printf("Domain tests passed!\n");
}

void test_repository() {
    printf("Starting repository tests...\n");
    Medicine_array *med_array = Medicine_array__create(0);
    assert(med_array->size == 0);

    Medicine *med = Medicine__create("test1", (float)(66.88), 12, 66);
    Medicine_array__add(&med_array, med);
    // testing the add
    assert(med_array->size == 1);
    assert(strcmp(med_array->array->name, "test1") == 0);
    assert(med_array->array->concentration == (float)(66.88));
    assert(med_array->array->quantity == 12);
    assert(med_array->array->price == 66);

    // test add same
    Medicine_array__add(&med_array, med);
    assert(med_array->array->quantity == 24);
    assert(med_array->size == 1);

    // test add 2
    Medicine *med2 = Medicine__create("test2", (float)(11), 12, 66);
    Medicine_array__add(&med_array, med2);
    assert(med_array->size == 2);
    assert(strcmp(med_array->array[1].name, "test2") == 0);
    assert(med_array->array[1].concentration == (float)(11));
    assert(med_array->array[1].quantity == 12);
    assert(med_array->array[1].price == 66);

    // testing delete
    Medicine_array__delete(&med_array, 0);
    assert(med_array->size == 1);
    assert(strcmp(med_array->array[0].name, "test2") == 0);
    assert(med_array->array[0].concentration == (float)(11));
    assert(med_array->array[0].quantity == 12);
    assert(med_array->array[0].price == 66);

    // testing update
    Medicine_array__update(&med_array, 0, "test3", (float)(88), 1, 3);
    assert(med_array->size == 1);
    assert(strcmp(med_array->array[0].name, "test3") == 0);
    assert(med_array->array[0].concentration == (float)(88));
    assert(med_array->array[0].quantity == 1);
    assert(med_array->array[0].price == 3);

    // cleanup
    Medicine__destroy(med);
    Medicine__destroy(med2);

    printf("Repository tests passed!\n");
}

void test_service() {
    printf("Starting service tests...\n");

    Medicine_array *med_array = Medicine_array__create(0);

    Service_medicine__add(&med_array, "test3a", (float)(66), 12, 66);
    Service_medicine__add(&med_array, "test1a", (float)(66), 2, 66);
    Service_medicine__add(&med_array, "test2b", (float)(66), 5, 66);

    // filter
    int *indexes = Service_medicine__filter(med_array, "\0");
    assert(indexes[0] == 1);
    assert(indexes[1] == 2);
    assert(indexes[2] == 0);
    free(indexes);

    int *indexes1 = Service_medicine__filter(med_array, "a");
    assert(indexes1[0] == 1);
    assert(indexes1[1] == 0);
    free(indexes1);

    // supply
    int *indexes2 = Service_medicine__supply(med_array, 6);
    assert(indexes2[0] == 1);
    assert(indexes2[1] == 2);
    free(indexes2);

    printf("Service tests passed!\n");
}
