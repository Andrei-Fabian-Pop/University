//
// Created by andre on 05/03/2022.
//

#pragma once

#include <stdio.h>
#include <math.h>

#include "../service/service.h"


void UI__start (Medicine_array** med_array);

void UI__add(Medicine_array** med_array);

void UI__delete(Medicine_array** med_array);

void UI__update(Medicine_array** med_array);

void UI__filter(Medicine_array** med_array);

void UI__supply(Medicine_array** med_arr);
