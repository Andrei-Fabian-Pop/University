//
// Created by andre on 05/03/2022.
//
#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[21];
    float concentration;
    unsigned int quantity;
    unsigned int price;
} Medicine;


void Medicine__init(Medicine* this, char *name, float concentration, int quantity, int price);

Medicine* Medicine__create(char *name, float concentration, int quantity, int price);

void Medicine__destroy(Medicine* this);
