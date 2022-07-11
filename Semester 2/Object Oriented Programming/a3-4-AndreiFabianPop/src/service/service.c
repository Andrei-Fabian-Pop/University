//
// Created by andre on 05/03/2022.
//

#include "service.h"

char* Service_medicine__add(Medicine_array **med_array, char *name, float concentration, int quantity, int price) {
    char *message = malloc(101 * sizeof(char));
    if (concentration <= 0 || concentration > 100) {
        strcpy_s(message, 101, "Err: Concentration value is invalid. No medicine created.\n");
    } else if (quantity <= 0) {
        strcpy_s(message, 101, "Err: Quantity value is invalid. No medicine created.\n");
    } else if (price <= 0) {
        strcpy_s(message, 101, "Err: Price value is invalid. No medicine created.\n");
    } else {
        Medicine* med = Medicine__create(name, concentration, quantity, price);
        Medicine_array__add(&(*med_array), med);
        strcpy_s(message, 101, "Medicine created and added successfully.\n");
    }

    return message;
}

char* Service_medicine__delete(Medicine_array** med_array, char* name, float concentration) {
    char *message = malloc(101 * sizeof(char));
    for (int i = 0; i < (*med_array)->size; ++i) {
        if (strcmp((*med_array)->array[i].name, name) == 0 &&
            (*med_array)->array[i].concentration == concentration) {
            // delete index
            Medicine_array__delete(&(*med_array), i);

            // confirmation message and break
            strcpy_s(message, 101, "Medicine successfully deleted.");
            return message;
        }
    }
    strcpy_s(message, 101, "No medicine with this name and concentration was found.");
    return message;
}

char* Service_medicine__update(Medicine_array** med_array, char* name, float concentration, char field, char *change) {
    char *message = malloc(101 * sizeof(char));
    for (int i = 0; i < (*med_array)->size; ++i) {
        if (strcmp((*med_array)->array[i].name, name) == 0 &&
            (*med_array)->array[i].concentration == concentration) {
            // check field matching the change
            if (field == '1') {
                // change should be type str
                Medicine_array__update(&(*med_array), i,
                                       change,
                                       (*med_array)->array[i].concentration,
                                       (*med_array)->array[i].quantity,
                                       (*med_array)->array[i].price);
            }
            else if (field == '2') {
                // change should be type float
                float aux;
                if (sscanf_s(change, "%4f", &aux) == 0) {
                    strcpy_s(message, 101, "Err: Invalid concentration(max 2 decimals).");
                    return message;
                }
                if (aux <= 0 || aux > 100) {
                    strcpy_s(message, 101, "Err: Concentration value is invalid. No medicine created.\n");
                } else {
                    Medicine_array__update(&(*med_array), i,
                                           (*med_array)->array[i].name,
                                           aux,
                                           (*med_array)->array[i].quantity,
                                           (*med_array)->array[i].price);
                }
            } else if (field == '3' || field == '4') {
                unsigned int aux;
                if (sscanf_s(change, "%d", &aux) == 0) {
                    strcpy_s(message, 101, "Err: Invalid unsigned integer.");
                    return message;
                }
                if (aux <= 0) {
                    strcpy_s(message, 101, "Err: Invalid value.");
                    return message;
                } else {
                    if (field == '3') {
                        Medicine_array__update(&(*med_array), i,
                                               (*med_array)->array[i].name,
                                               (*med_array)->array[i].concentration,
                                               aux,
                                               (*med_array)->array[i].price);
                    } else {
                        Medicine_array__update(&(*med_array), i,
                                               (*med_array)->array[i].name,
                                               (*med_array)->array[i].concentration,
                                               (*med_array)->array[i].quantity,
                                               aux);
                    }
                }
            }

            // confirmation message and break
            strcpy_s(message, 101, "Medicine successfully updated.");
            return message;
        }
    }
    strcpy_s(message, 101, "Err: No medicine with this name and concentration was found.");
    return message;
}

int* Service_medicine__filter(const Medicine_array* med_array, const char* key) {
    char* ret;
    int *index_arr = malloc((med_array->size + 1) * sizeof (int)), index = 0;

    if (key[0] != '\0') {
        for (int i = 0; i < med_array->size; ++i) {
            ret = strstr(med_array->array[i].name, key);

            if (ret != NULL) {
                index_arr[index++] = i;
            }
        }
    } else {
        index = med_array->size;
        for (int i = 0; i < index; ++i) {
            index_arr[i] = i;
        }
    }

    for (int i = 0; i < index; ++i) {
        for (int j = i+1; j < index; ++j) {
            if (strcmp(med_array->array[index_arr[i]].name, med_array->array[index_arr[j]].name) > 0) {
                int aux = index_arr[i];
                index_arr[i] = index_arr[j];
                index_arr[j] = aux;
            }
        }
    }
    index_arr[index] = -1;

    return &(*index_arr);
}

int* Service_medicine__supply(const Medicine_array* med_array, int min_quantity) {
    int *index_arr = malloc((med_array->size + 1) * sizeof (int)), index = 0;

    for (int i = 0; i < med_array->size; ++i) {
        if (med_array->array[i].quantity < min_quantity) {
            index_arr[index++] = i;
        }
    }

    index_arr[index] = -1;

    return &(*index_arr);
}
