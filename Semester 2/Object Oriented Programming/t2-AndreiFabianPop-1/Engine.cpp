//
// Created by andrew on 05/05/22.
//

#include "Engine.h"

Engine::Engine(const std::string& fuelType, double basePrice) {
    this->fuelType = fuelType;
    this->basePrice = basePrice;
}

double Engine::getPrice() const {
    return this->basePrice;
}

const std::string &Engine::getFuelType() const {
    return fuelType;
}

double Engine::getBasePrice() const {
    return basePrice;
}

ElectricEngine::ElectricEngine(const std::string &fuelType, double basePrice, int autonomy) : Engine(fuelType, basePrice) {
    this->fuelType = fuelType;
    this->basePrice = basePrice;
    this->autonomy = autonomy;
}

double ElectricEngine::getPrice() const {
    return this->basePrice + autonomy * 0.01;
}

std::string ElectricEngine::toString() {
    return "Fuel: " + this->fuelType + " | Price: " + std::to_string(this->basePrice) + " | Autonomy " + std::to_string(autonomy);
}

int ElectricEngine::getAutonomy() const {
    return autonomy;
}

double TurboEngine::getPrice() const {
    return this->basePrice + ((fuelType == "gasoline") ? 0.01*100 : 0.01*150);
}

std::string TurboEngine::toString() {
    return "Fuel: " + this->fuelType + " | Price: " + std::to_string(this->basePrice);
    ;
}

TurboEngine::TurboEngine(const std::string &fuelType, double basePrice) : Engine(fuelType, basePrice) {
    this->fuelType = fuelType;
    this->basePrice = basePrice;
}
