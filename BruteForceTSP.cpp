#include "BruteForceTSP.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <chrono>


BruteForceTSP::BruteForceTSP(std::vector<City> cities, Car car) : AbstractTSP(cities, car) {
    n = cities.size();
    k = 1.02; //a set coefficient of the diffrence in fuel consumption based on elevation. https://www.quora.com/How-many-feet-of-elevation-increase-is-equivalent-in-fuel-usage-to-driving-an-extra-mile-with-no-elevation-change
    fuelConsumptionMatrix = std::vector<std::vector<double>>(n, std::vector<double>(n));;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            double dx = cities[i].getX() - cities[j].getX();
            double dy = cities[i].getY() - cities[j].getY();
            double dz = cities[j].getZ() - cities[i].getZ(); //i and j are swapped because the fuel consumption should get lower if a car is going downhill and up if it's going uphill
            double distance = std::sqrt(dx * dx + dy * dy + dz * dz);

            if (distance == 0) {
                fuelConsumptionMatrix[i][j] = -1;
                continue;
            }

            double fuelConsumption = (distance / 100) * (car.getAvgFuelConsumption() + k * dz / 100);
            if (fuelConsumption > 0) { fuelConsumptionMatrix[i][j] = fuelConsumption; }
            else { fuelConsumptionMatrix[i][j] = 0; }
        }
    }
}

void BruteForceTSP::getPermutations(std::vector<int>& cities, int start, std::vector<std::vector<int>>& permutations) {
    if (start == cities.size() - 1) {
        permutations.push_back(cities);
        return;
    }
    
    for (int i = start; i < cities.size(); i++) {
        std::swap(cities[start], cities[i]);
        BruteForceTSP::getPermutations(cities, start + 1, permutations);
        std::swap(cities[start], cities[i]); 
    }
}

void BruteForceTSP::solveTSP() {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<int> citiesID(n);

    for (int i=0; i<n; i++){
        citiesID[i] = i;
    }
    std::vector<int> solutionTSP;

    // for (int i = 0; i < n; i++) { //PRINTING THE MATRIX FOR TESTING
    //     for (int j = 0; j < n; j++) {
    //         std::cout << fuelConsumptionMatrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    double minConsumedFuel = std::numeric_limits<double>::max();
    int savePermutation;


    do {
        std::vector<int> updatedPermutations = citiesID;
        updatedPermutations.push_back(citiesID[0]);
        double curConsumedFuel = 0;


        for (int j = 0; j < n; j++) {
            curConsumedFuel += fuelConsumptionMatrix[updatedPermutations[j]][updatedPermutations[(j+1) % n]];
            if (curConsumedFuel > minConsumedFuel) {break;}
        }
        if (curConsumedFuel < minConsumedFuel) {
            minConsumedFuel = curConsumedFuel;
            solutionTSP = updatedPermutations;
        }

    } while (std::next_permutation(citiesID.begin(), citiesID.end()));

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();



    for (int i = 0; i<n; i++) {
        std::cout << solutionTSP[i] << "->";
    }
    std::cout << solutionTSP[n] << "\nBruteForce: The consumed fuel using this route was: " << minConsumedFuel << std::endl;

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    nlohmann::json jsonData;
    jsonData["route"] = solutionTSP;

    std::ofstream outputFile("./solution/solutionBruteForce.json");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open json file." << std::endl;
        return;
    }
    outputFile << jsonData.dump(4);
    outputFile.close();
}
