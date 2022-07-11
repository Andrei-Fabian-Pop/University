//
// Created by andrew on 05/05/22.
//

#include "UI.h"


UI::UI(Service serv) {
    this->service = std::move(serv);
}

void UI::printOptions() {
    std::cout << "0. Exit\n";
    std::cout << "1. Add new car\n";
    std::cout << "2. Print all\n";
    std::cout << "3. Save to file\n";
    std::cout << ">";
}

void UI::start() {
    while (true) {
        int opt;
        printOptions();
        std::cin >> opt;
        if (opt == 0) {
            break;
        } else if (opt == 1) {
            addCar();
        } else if (opt == 2) {
            showAll();
        } else if (opt == 3) {
            saveToFile();
        }
    }
}

void UI::addCar() {
    int numberOfDoors;
    std::string engineType;
    std::string fuelType;
    int autonomy;

    std::cout << "Nr of doors:";
    std::cin >> numberOfDoors;
    if (numberOfDoors != 2 && numberOfDoors != 4){
        std::cerr << "Invalid number.\n";
        return;
    }

    std::cout << "Engine type:";
    std::cin >> engineType;
    if (engineType != "electric" && engineType != "turbo") {
        std::cerr << "Invalid type.\n";
    }

    std::cout << "Fuel type:";
    std::cin >> fuelType;
    if (fuelType != "gasoline" && fuelType != "diesel") {
        std::cerr << "Invalid type.\n";
    }

    if (engineType == "electric") {
        std::cout << "Autonomy:";
        std::cin >> autonomy;
    } else {
        autonomy = -1;
    }

    Car car = service.addCar(numberOfDoors, engineType, fuelType, autonomy);

    std::cout << "Car added:\n";
    std::cout << "Price: " << car.computePrice() <<
                "\nDoors: " << numberOfDoors <<
                "\nEngine type: " << engineType <<
                "\nFuel Type: " << fuelType <<
                "\nAutonomy: " << autonomy << std::endl;
}

void UI::showAll() {
    std::vector<Car> carList = service.getAll();
    for (auto& car : carList) {
        std::cout << "Price: " << car.computePrice() <<
          " | Doors: " << car.getNumberOfDoors()  <<
          " | Engine type: " << car.engineType <<
          "| " << car.getEngine()->toString() << std::endl;
    }
}

void UI::saveToFile() {
    std::string file;
    double price;

    std::cout << "Enter file name:";
    std::cin >> file;

    std::cout << "Enter min price:";
    std::cin >> price;

    Service::writeToFile(file, service.getCarsWithMaxPrice(price));
}


