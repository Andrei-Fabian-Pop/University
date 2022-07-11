//
// Created by andrew on 05/05/22.
//

#ifndef T2_ANDREIFABIANPOP_1_UI_H
#define T2_ANDREIFABIANPOP_1_UI_H

#include <iostream>
#include <utility>

#include "Service.h"


class UI {
private:
    Service service;
public:
    explicit UI(Service serv);
    void start();
    static void printOptions();
    void addCar();
    void showAll();
    void saveToFile();
};


#endif //T2_ANDREIFABIANPOP_1_UI_H
