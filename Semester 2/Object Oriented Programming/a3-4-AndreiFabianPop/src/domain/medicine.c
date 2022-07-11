//
// Created by andre on 05/03/2022.
//

#include "medicine.h"

void Medicine__init(Medicine* this, char *name, float concentration, int quantity, int price) {
    strcpy_s(this->name, 21, name);
    this->concentration = concentration;
    this->quantity = quantity;
    this->price = price;
}

Medicine* Medicine__create(char *name, float concentration, int quantity, int price) {
    Medicine *med = malloc(sizeof (Medicine));
    Medicine__init(med, name, concentration, quantity, price);
    return med;
}

void Medicine__destroy(Medicine* this) {
    if (this) {
        free(this);
    }
}
