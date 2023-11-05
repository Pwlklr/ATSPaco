#ifndef _CAR_H_
#define _CAR_H_

#include <string>

class Car {
private:
    std::string model;
    float avgFuelConsumption;

public:
    Car(std::string _model, float avgFuelConsumption);
    std::string getModel() const;
    float getAvgFuelConsumption() const;
};

#endif