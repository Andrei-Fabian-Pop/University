//
// Created by andrew on 05/05/22.
//

#include "Service.h"

Engine *Service::createEngine(const std::string& engineType, const std::string& fuelType, int autonomy) {
    Engine* engine;
    if (engineType == "electric") {
        engine = new ElectricEngine(fuelType, 3000, autonomy);
    } else if (engineType == "turbo") {
        engine = new TurboEngine(fuelType, 3000);
    }
    return engine;
}

Car Service::addCar(int numberOfDoors, const std::string& engineType, const std::string& fuelType, int autonomy) {
    Engine* engine = this->createEngine(engineType, fuelType, autonomy);
    Car car(engine, numberOfDoors, engineType);

    this->carList.push_back(car);
    return car;
}

std::vector<Car> Service::getCarsWithMaxPrice(double maxPrice) {
    std::vector<Car> aux;
    for (auto& car: this->carList) {
        if (car.computePrice() < maxPrice) {
            aux.push_back(car);
        }
    }
    return aux;
}

void Service::writeToFile(const std::string& fileName, std::vector<Car> carVector) {
    std::ofstream g(fileName);
    for (auto &car: carVector) {
        g << "Price: " << car.computePrice() <<
          " | Doors: " << car.getNumberOfDoors()  <<
          " | Engine type: " << car.engineType <<
          "| " << car.getEngine()->toString() << std::endl;
    }
}

std::vector<Car> Service::getAll() {
    return this->carList;
}
