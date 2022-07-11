//
// Created by andrew on 05/05/22.
//

#include "Car.h"

#include <utility>

Car::Car(Engine *e, int doors, std::string engineType) {
    this->engine = e;
    this->numberOfDoors = doors;
    this->engineType = std::move(engineType);
}

double Car::computePrice() {
    return ((this->numberOfDoors == 2) ? 7000 : 8500) + engine->getPrice();
}

int Car::getNumberOfDoors() const {
    return numberOfDoors;
}

Engine *Car::getEngine() const {
    return engine;
}
