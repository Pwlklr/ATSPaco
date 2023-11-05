#include "Car.h"
#include <iostream>


Car::Car(std::string _model, float _avgFuelConsumption) : model(_model), avgFuelConsumption(_avgFuelConsumption) {}

std::string Car::getModel() const {
    return model;
}

float Car::getAvgFuelConsumption() const {
    return avgFuelConsumption;
}