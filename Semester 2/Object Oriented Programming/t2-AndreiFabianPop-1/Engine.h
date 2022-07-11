//
// Created by andrew on 05/05/22.
//

#ifndef T2_ANDREIFABIANPOP_1_ENGINE_H
#define T2_ANDREIFABIANPOP_1_ENGINE_H

#include <string>


class Engine {
protected:
    std::string fuelType;
    double basePrice;
public:
    explicit Engine(const std::string& fuelType, double basePrice);

    virtual double getPrice() const;
    virtual std::string toString()=0;

    const std::string &getFuelType() const;

    double getBasePrice() const;
};

class ElectricEngine : public Engine {
private:
    int autonomy;
public:
    explicit ElectricEngine(const std::string &fuelType, double basePrice, int autonomy);

    double getPrice() const override;
    std::string toString() override;

    int getAutonomy() const;
};

class TurboEngine : public Engine {
public:
    explicit TurboEngine(const std::string &fuelType, double basePrice);

    double getPrice() const override;
    std::string toString() override;
};


#endif //T2_ANDREIFABIANPOP_1_ENGINE_H
