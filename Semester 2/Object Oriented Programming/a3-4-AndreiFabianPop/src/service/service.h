//
// Created by andre on 05/03/2022.
//

#pragma once

#include <string.h>
#include <stdlib.h>

#include "../repository/repository.h"

char* Service_medicine__add(Medicine_array **med_array, char *name, float concentration, int quantity, int price);
// Validates and makes a Medicine struct out of the name, concentration, quantity and price fields. After that it adds
// it to the specified med_array. If a material that already exists is added, its quantity will be modified
// (the new quantity is added to the existing one). It returns a message representing the output of the function,
// Error (and it's user message for fixing it) or success.

char* Service_medicine__delete(Medicine_array** med_array, char* name, float concentration);
// Searches for a Medicine with the provided proprieties (name and concentration) and, if found, it will be deleted,
// if not, an according message will be returned

char* Service_medicine__update(Medicine_array** med_array, char* name, float concentration, char field, char *change);
// Searches for a Medicine with the provided proprieties (name and concentration) and, if found, it will be updated,
// if not, an according message will be returned. The field represents the part to update and the change the string
// that represents the updated part

int* Service_medicine__filter(const Medicine_array* med_array, const char* key);
// See all available medicines containing a given string (if the string is empty,
// all the available medicines will be considered), sorted ascending by medicine name.
// The key represents the string to me matched.

int* Service_medicine__supply(const Medicine_array* med_array, int min_quantity);
//See only those medicines that are in short supply (quantity less than X items, where the value of X is user-provided).
