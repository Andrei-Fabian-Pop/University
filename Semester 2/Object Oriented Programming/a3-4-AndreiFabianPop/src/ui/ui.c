//
// Created by andre on 05/03/2022.
//

#include "ui.h"

#define LAST_OPTION_ID '5'

void print_options() {
    printf("Choose an option:\n");
    printf("0. Exit program\n");
    printf("1. Add medicine\n");
    printf("2. Delete medicine\n");
    printf("3. Update medicine\n");
    printf("4. See all medicine containing a string\n");
    printf("5. See all medicine in quantity less than a value\n");
}

int validate_input(char c) {
    if (c < '0' || c > LAST_OPTION_ID) {
        return 0;
    }
    return 1;
}

char get_user_input() {
    char user_input;
    int aux;
    scanf_s(" %c", &user_input, (unsigned)(1));
    while ((aux = getchar()) != '\n' && aux != EOF);

    return user_input;
}

void UI__add(Medicine_array** med_array) {
    char name[21];
    float concentration;
    int quantity, price;

    printf("Enter the name(max 20 characters):\n");
    scanf_s("%21s", name, (unsigned)(21));

    printf("Enter the concentration:\n");
    scanf_s("%f", &concentration);
    concentration = roundf(concentration*100)/100;

    printf("Enter the quantity:\n");
    scanf_s("%d", &quantity);

    printf("Enter the price:\n");
    scanf_s("%d", &price);

    char* message = Service_medicine__add(&(*med_array), name, concentration, quantity, price);
    printf("%s\n", message);
    free(message);
}

void UI__delete(Medicine_array** med_array) {
    char name[21];
    float concentration;

    printf("Enter the name(max 20 characters):\n");
    scanf_s("%21s", name, (unsigned)(21));

    printf("Enter the concentration:\n");
    scanf_s("%f", &concentration);
    concentration = roundf(concentration*100)/100;

    char *message = Service_medicine__delete(&(*med_array), name, concentration);
    printf("%s\n", message);
    free(message);
}

void UI__update(Medicine_array** med_array) {
    char name[21], change[21], user_input;
    float concentration;

    printf("Enter the name(max 20 characters):\n");
    scanf_s("%21s", name, (unsigned)(21));

    printf("Enter the concentration:\n");
    scanf_s("%f", &concentration);
    concentration = roundf(concentration*100)/100;

    printf("What do you want to update?\n1. name\n2. concentration\n3. quantity\n4. price\n");
    user_input = get_user_input();

    if (user_input >= '1' && user_input <= '4') {
        printf("Enter the new value:\n");
        scanf_s("%21s", change, (unsigned)(21));
        char* message = Service_medicine__update(&(*med_array), name, concentration, user_input, change);
        printf("%s\n", message);
        free(message);
    } else {
        printf("Invalid update field. No changes were made.\n");
    }
}

void UI__filter(Medicine_array** med_array) {
    int i=0;
    char key[21];
    printf("Enter the key(or leave empty):\n");
    do {
        key[i] = (char)(getchar());
    } while (key[i++] != '\n');
    key[--i] = '\0';

    int *index_list = Service_medicine__filter(*med_array, key);

    i=0;
    printf("Storage:\n");
    while (index_list[i] != -1) {
        printf("%s(%f%%), quantity in storage is %d and the price is %d.\n",
               (*med_array)->array[index_list[i]].name,
               (*med_array)->array[index_list[i]].concentration,
               (*med_array)->array[index_list[i]].quantity,
               (*med_array)->array[index_list[i]].price);
        ++i;
    }
    free(index_list);
}

void UI__supply(Medicine_array** med_array) {
    int min_quantity, *index_list;
    printf("Enter the minimum quantity:\n");
    scanf_s("%d", &min_quantity);
    if (min_quantity <= 0) {
        printf("Err: The minimum quantity cannot be 0 or less.\n");
        return;
    } else {
        index_list = Service_medicine__supply(*med_array, min_quantity);
    }

    int i=0;
    printf("Storage:\n");
    while (index_list[i] != -1) {
        printf("%s(%f%%), quantity in storage is %d and the price is %d.\n",
               (*med_array)->array[index_list[i]].name,
               (*med_array)->array[index_list[i]].concentration,
               (*med_array)->array[index_list[i]].quantity,
               (*med_array)->array[index_list[i]].price);
        ++i;
    }
    free(index_list);
}

void UI__start(Medicine_array** med_array) {
    char user_input = 0;
    while (user_input != '0') {
        print_options();
        user_input = get_user_input();

        if (validate_input(user_input) == 0) {
            printf("Invalid input.\n");
        } else {
            if (user_input == '1') {
                UI__add(&(*med_array));
            } else if (user_input == '2') {
                UI__delete(&(*med_array));
            } else if (user_input == '3') {
                UI__update(&(*med_array));
            } else if (user_input == '4') {
                UI__filter(&(*med_array));
            } else if (user_input == '5') {
                UI__supply(&(*med_array));
            }
        }
    }
    printf("Exiting program.");
}
