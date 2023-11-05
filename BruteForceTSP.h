#ifndef BRUTEFORCETSP_H_
#define BRUTEFORCETSP_H_

#include "City.h"
#include "AbstractTSP.h"
#include "Car.h"
#include <vector>

class BruteForceTSP : public AbstractTSP{
private:
    std::vector<std::vector<double>> fuelConsumptionMatrix;
    int n;
    float k;
public:
    BruteForceTSP(std::vector<City>, Car car);

    void getPermutations(std::vector<int>& cities, int start, std::vector<std::vector<int>>& permutations);
    void solveTSP();
};

#endif