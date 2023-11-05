#include "GreedyTSP.h"


#include "nlohmann/json.hpp"
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>
#include <chrono>


GreedyTSP::GreedyTSP(std::vector<City> cities, Car car) : AbstractTSP(cities, car) {
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

bool GreedyTSP::compareByFuel(const std::tuple<float, int, int>& a, const std::tuple<float, int, int>& b) {
    return std::get<0>(a) < std::get<0>(b);
}

void GreedyTSP::solveTSP() {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // for (int i = 0; i < n; i++) { //PRINTING THE MATRIX FOR TESTING
    //     for (int j = 0; j < n; j++) {
    //         std::cout << fuelConsumptionMatrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    int startingCity = 0;

    std::vector<int> solutionTSP(n+1, -1);

    solutionTSP[0] = startingCity;
    double consumed_fuel = 0;

    for (int i=0; i < n - 1; i++) {
        double minValue = std::numeric_limits<double>::max();
        int minValueIndex = 0;
        for (int j = 0; j < n; j++) {
            if (j == solutionTSP[i]) {continue;}
            if (std::count(solutionTSP.begin(), solutionTSP.end(), j)) {continue;}

            if (fuelConsumptionMatrix[solutionTSP[i]][j] < minValue) {
            minValue = fuelConsumptionMatrix[solutionTSP[i]][j];
            minValueIndex = j;
            }
        }
        solutionTSP[i+1] = minValueIndex;
        consumed_fuel += fuelConsumptionMatrix[solutionTSP[i]][solutionTSP[i+1]];
    }

    solutionTSP[n] = solutionTSP[0];
    consumed_fuel += fuelConsumptionMatrix[solutionTSP[n-1]][solutionTSP[0]];

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();



    for (int i = 0; i < n; i++) {
        std::cout << solutionTSP[i] << "->";
    }
    std::cout << solutionTSP[n] << "\nGreedy: The consumed fuel using this route was: " << consumed_fuel << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    nlohmann::json jsonData;
    jsonData["route"] = solutionTSP;

    std::ofstream outputFile("./solution/solutionGreedy.json");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open json file." << std::endl;
        return;
    }
    outputFile << jsonData.dump(4);
    outputFile.close();

}



void GreedyTSP::solveTSP(unsigned int i) {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // for (int i = 0; i < n; i++) { //PRINTING THE MATRIX FOR TESTING
    //     for (int j = 0; j < n; j++) {
    //         std::cout << fuelConsumptionMatrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    int startingCity = i;


    std::vector<int> solutionTSP(n+1, -1);
    solutionTSP[0] = startingCity;
    double consumed_fuel = 0;

    for (int i=0; i < n - 1; i++) {
        double minValue = std::numeric_limits<double>::max();
        int minValueIndex = 0;
        for (int j = 0; j < n; j++) {
            if (j == solutionTSP[i]) {continue;}
            if (std::count(solutionTSP.begin(), solutionTSP.end(), j)) {continue;}

            if (fuelConsumptionMatrix[solutionTSP[i]][j] < minValue) {
            minValue = fuelConsumptionMatrix[solutionTSP[i]][j];
            minValueIndex = j;
            }
        }
        solutionTSP[i+1] = minValueIndex;
        consumed_fuel += fuelConsumptionMatrix[solutionTSP[i]][solutionTSP[i+1]];
    }

    solutionTSP[n] = solutionTSP[0];
    consumed_fuel += fuelConsumptionMatrix[solutionTSP[n-1]][solutionTSP[0]];

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    for (int i = 0; i<n; i++) {
        std::cout << solutionTSP[i] << "->";
    }
    std::cout << solutionTSP[n] << "\nGreedy: The consumed fuel using this route was: " << consumed_fuel << std::endl;

    

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    nlohmann::json jsonData;
    jsonData["route"] = solutionTSP;

    std::ofstream outputFile("./solution/solutionGreedy.json");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open json file." << std::endl;
        return;
    }
    outputFile << jsonData.dump(4);
    outputFile.close();

}


void GreedyTSP::solveTSPAC() {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // for (int i = 0; i < n; i++) { //PRINTING THE MATRIX FOR TESTING
    //     for (int j = 0; j < n; j++) {
    //         std::cout << fuelConsumptionMatrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    int startingCity = 0;

    std::vector<int> solutionTSP(n+1, -1);

    double bestConsumedFuel = std::numeric_limits<double>::max();
    std::vector<int> bestSolutionTSP;
    double consumed_fuel;

    for (int count = 0; count < n; count++) {
        std::vector<int> solutionTSP(n+1, -1);
        solutionTSP[0] = count;
        consumed_fuel = 0;

        for (int i=0; i < n - 1; i++) {
            double minValue = std::numeric_limits<double>::max();
            int minValueIndex = 0;
            for (int j = 0; j < n; j++) {
                if (j == solutionTSP[i]) {continue;}
                if (std::count(solutionTSP.begin(), solutionTSP.end(), j)) {continue;}

                if (fuelConsumptionMatrix[solutionTSP[i]][j] < minValue) {
                minValue = fuelConsumptionMatrix[solutionTSP[i]][j];
                minValueIndex = j;
                }
            }
            solutionTSP[i+1] = minValueIndex;
            consumed_fuel += fuelConsumptionMatrix[solutionTSP[i]][solutionTSP[i+1]];
        }

        solutionTSP[n] = solutionTSP[0];
        consumed_fuel += fuelConsumptionMatrix[solutionTSP[n-1]][solutionTSP[0]];

        if (consumed_fuel < bestConsumedFuel){ 
            bestConsumedFuel = consumed_fuel;
            bestSolutionTSP = solutionTSP;
        }

    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();



    for (int i = 0; i<n; i++) {
        std::cout << bestSolutionTSP[i] << "->";
    }
    std::cout << bestSolutionTSP[n] << "\nGreedyASC: The consumed fuel using this route was: " << bestConsumedFuel << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


    nlohmann::json jsonData;
    jsonData["route"] = solutionTSP;

    std::ofstream outputFile("./solution/solutionGreedyASC.json");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open json file." << std::endl;
        return;
    }
    outputFile << jsonData.dump(4);
    outputFile.close();
}