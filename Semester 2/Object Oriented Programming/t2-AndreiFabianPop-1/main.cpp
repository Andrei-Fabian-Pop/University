//
// Created by andrew on 05/05/22.
//

#include "Service.h"
#include "UI.h"

int main() {
    Service service;
    service.addCar(2, "electric", "gasoline", 400);
    service.addCar(4, "turbo", "gasoline", -1);
    service.addCar(2, "turbo", "diesel", -1);
    UI ui(service);
    ui.start();

    return 0;
}