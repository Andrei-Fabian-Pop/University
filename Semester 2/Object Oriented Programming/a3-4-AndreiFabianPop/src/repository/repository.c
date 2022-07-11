//
// Created by andre on 05/03/2022.
//

#include "repository.h"

void Medicine_array__destroy(Medicine_array* array) {
    free(array->array);
}

void Medicine_array__init(Medicine_array** old_array, Medicine_array* new_array) {
    if ((*old_array)->size == new_array->size) {
        printf("Error. New array has the same amount of elements as the old array.\n");
    } else {
        int smallest_size = ((*old_array)->size < new_array->size) ? (*old_array)->size : new_array->size;
        for (int i = 0; i < smallest_size; ++i) {
            strcpy_s(new_array->array[i].name, 21, (*old_array)->array[i].name);
            new_array->array[i].concentration = (*old_array)->array[i].concentration;
            new_array->array[i].quantity = (*old_array)->array[i].quantity;
            new_array->array[i].price = (*old_array)->array[i].price;
        }
        Medicine_array__destroy(*old_array);
        (*old_array) = new_array;
    }
}

Medicine_array* Medicine_array__create(int size) {
    Medicine_array *med = malloc(sizeof(Medicine_array));
    med->size = size;
    med->array = malloc(size * sizeof(Medicine));
    return med;
}

void Medicine_array__delete(Medicine_array** med_array, int index) {
    // copy the last med_array element instead of the deleted med
    strcpy_s((*med_array)->array[index].name, 21, (*med_array)->array[(*med_array)->size-1].name);
    (*med_array)->array[index].concentration = (*med_array)->array[(*med_array)->size-1].concentration;
    (*med_array)->array[index].quantity = (*med_array)->array[(*med_array)->size-1].quantity;
    (*med_array)->array[index].price = (*med_array)->array[(*med_array)->size-1].price;

    // change the size of the medicine so the last med cannot be accessed
    --(*med_array)->size;
}

void Medicine_array__add(Medicine_array** med_array, Medicine* medicine) {
    int inc_quantity = 0;
    for (int i = 0; i < (*med_array)->size; ++i) {
        if (strcmp((*med_array)->array[i].name, medicine->name) == 0 &&
            (*med_array)->array[i].concentration == medicine->concentration) {
            (*med_array)->array[i].quantity += medicine->quantity;
            inc_quantity++;
            break;
        }
    }
    if (inc_quantity == 0) {
        // add a new element
        Medicine_array *new_array = Medicine_array__create((*med_array)->size + 1);
        Medicine_array__init(&(*med_array), new_array);

        strcpy_s((*med_array)->array[(*med_array)->size-1].name, 21, medicine->name);
        (*med_array)->array[(*med_array)->size-1].concentration = medicine->concentration;
        (*med_array)->array[(*med_array)->size-1].quantity = medicine->quantity;
        (*med_array)->array[(*med_array)->size-1].price = medicine->price;
    }
}

void Medicine_array__update(Medicine_array** med_array, int index,
                            char *name, float concentration, unsigned int quantity, unsigned int price) {
    strcpy_s((*med_array)->array[index].name, 21, name);
    (*med_array)->array[index].concentration = concentration;
    (*med_array)->array[index].quantity = quantity;
    (*med_array)->array[index].price = price;
}