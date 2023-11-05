#ifndef _RANDOMISEDGREEDYTSP_H_
#define _RANDOMISEDGREEDYTSP_H_

#include "City.h"
#include "AbstractTSP.h"
#include "Car.h"
#include <vector>

class RandomisedGreedyTSP : public AbstractTSP{
private:
    std::vector<std::vector<double>> fuelConsumptionMatrix;
    int n;
    float k;
public:
    RandomisedGreedyTSP(std::vector<City>, Car car);

    void solveTSP();
};

#endif