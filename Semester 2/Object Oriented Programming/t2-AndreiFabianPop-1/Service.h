//
// Created by andrew on 05/05/22.
//

#ifndef T2_ANDREIFABIANPOP_1_SERVICE_H
#define T2_ANDREIFABIANPOP_1_SERVICE_H

#include <vector>
#include <string>
#include <fstream>

#include "Car.h"
#include "Engine.h"


class Service {
private:
    std::vector<Car> carList;
    static Engine* createEngine(const std::string& engineType, const std::string& fuelType, int autonomy);
public:
    Car addCar(int numberOfDoors, const std::string& engineType, const std::string& fuelType, int autonomy);
    std::vector<Car> getCarsWithMaxPrice(double maxPrice);
    static void writeToFile(const std::string& fileName, std::vector<Car> carVector);
    std::vector<Car> getAll();
};


#endif //T2_ANDREIFABIANPOP_1_SERVICE_H
