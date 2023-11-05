#ifndef _ABSTRACTTSP_H_
#define _ABSTRACTTSP_H_

#include "City.h"
#include "Car.h"
#include "AbstractTSP.h"
#include <vector>

class AbstractTSP {
protected:
    std::vector<City> cities;
    Car car;

public:
    AbstractTSP(std::vector<City> cities, Car car);

    virtual void solveTSP() = 0;
};
#endif