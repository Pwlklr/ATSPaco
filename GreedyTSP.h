#ifndef _GREEDYTSP_H_
#define _GREEDYTSP_H_

#include "AbstractTSP.h"
#include <vector>

class GreedyTSP : public AbstractTSP {
private:
    std::vector<std::vector<double>> fuelConsumptionMatrix;
    int n;
    float k;
public:
    GreedyTSP(std::vector<City>, Car car);

    void solveTSP() override;
    void solveTSP(unsigned int i);
    void solveTSPAC();

    static bool compareByFuel(const std::tuple<float, int, int>& a, const std::tuple<float, int, int>& b);
};
#endif