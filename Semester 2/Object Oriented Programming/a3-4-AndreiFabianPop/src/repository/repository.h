//
// Created by andre on 05/03/2022.
//

#pragma once
#include "../domain/medicine.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Medicine *array;
    int size;
} Medicine_array;

void Medicine_array__init(Medicine_array** old_array, Medicine_array* new_array);
// Initialises an old array with a new one

Medicine_array* Medicine_array__create(int size);
// Allocates a Medicine_array

void Medicine_array__destroy(Medicine_array* array);
// Deallocates a medicine array

void Medicine_array__add(Medicine_array** med_array, Medicine* medicine);
// Adds a medicine to the medicine array

void Medicine_array__delete(Medicine_array** med_array, int index);
// Deletes a medicine from the medicine array

void Medicine_array__update(Medicine_array** med_array, int index,
                            char *name, float concentration, unsigned int quantity, unsigned int price);
// Updates the medicine array at index 'index' with the new specifications
