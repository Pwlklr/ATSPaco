#ifndef HEURISTICTSP_H_
#define HEURISTICTSP_H_

#include "City.h"
#include "AbstractTSP.h"
#include "Car.h"
#include <vector>
#include <chrono>

class HeuristicTSP : public AbstractTSP {
private:
    int n;
    double pheromoneMultiplier;
    double distanceMultiplier;
    double evaporationRate;


public:
    HeuristicTSP(std::vector<City>, Car car, double _pheromoneMultiplier, double _distanceMultiplier, double _evaporationRate);

    void solveTSP();
};

#endif