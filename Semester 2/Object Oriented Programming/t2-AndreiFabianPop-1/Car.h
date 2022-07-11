//
// Created by andrew on 05/05/22.
//

#ifndef T2_ANDREIFABIANPOP_1_CAR_H
#define T2_ANDREIFABIANPOP_1_CAR_H

#include "Engine.h"

class Car {
private:
    int numberOfDoors;
    Engine* engine;
public:
    std::string engineType;
    int getNumberOfDoors() const;
    Engine *getEngine() const;
    explicit Car(Engine* e, int doors, std::string engineType);
    double computePrice();
};


#endif //T2_ANDREIFABIANPOP_1_CAR_H
