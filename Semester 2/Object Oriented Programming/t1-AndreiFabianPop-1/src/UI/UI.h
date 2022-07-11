//
// Created by andre on 07/04/2022.
//

#ifndef T1_ANDREIFABIANPOP_1_UI_H
#define T1_ANDREIFABIANPOP_1_UI_H

#include "../Service/Service.h"
#include <iostream>

class UI {
private:
    Service service;
public:
    explicit UI(Service serv);

    static void print_options();
    void start();

    void remove();
    void print_schools();
    void mark();
};


#endif //T1_ANDREIFABIANPOP_1_UI_H
