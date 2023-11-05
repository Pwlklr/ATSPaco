#include "HeuristicTSP.h"
#include "Car.h"
#include "City.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>
#include <chrono>
#include <random>

HeuristicTSP::HeuristicTSP(std::vector<City> cities, Car car, double _pheromoneMultiplier, double _distanceMultiplier, double _evaporationRate) : AbstractTSP(cities, car), pheromoneMultiplier(_pheromoneMultiplier), distanceMultiplier(_distanceMultiplier), evaporationRate(_evaporationRate) {
    n = cities.size();
}

class Data {
public:
	std::vector<City> cities;
    Car car;
    int n;
    double maxFuelConsumption;
    unsigned int pheromoneMultiplier;
    unsigned int distanceMultiplier;
    std::vector<std::vector<double>> pheromoneMatrix;
    std::vector<std::vector<double>> fuelConsumptionMatrix;
    std::vector<std::vector<double>> visibilityMatrix;


    Data(std::vector<City> cities, Car car) : cities(cities), car(car){
        n = cities.size();
        pheromoneMatrix.assign(n, std::vector<double>(n, n)); 
        fuelConsumptionMatrix.assign(n, std::vector<double>(n, 0.0));
        visibilityMatrix.assign(n, std::vector<double>(n, 0.0));

        float k = 1.02; //a set coefficient of the diffrence in fuel consumption based on elevation. https://www.quora.com/How-many-feet-of-elevation-increase-is-equivalent-in-fuel-usage-to-driving-an-extra-mile-with-no-elevation-change
        maxFuelConsumption = 0;
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
                if (maxFuelConsumption < fuelConsumption) {
                    maxFuelConsumption = fuelConsumption;
                }
                if (fuelConsumption > 0) { fuelConsumptionMatrix[i][j] = fuelConsumption; }
                else { fuelConsumptionMatrix[i][j] = 0; }
            }
        }

        for (int i = 0; i < n; i++) {  
            for (int j = 0; j < n; j++) {
                visibilityMatrix[i][j] =  n / fuelConsumptionMatrix[i][j];
            }
        }
    }
    
    double tourCost(std::vector<int> tour) {
        double ConsumedFuel = 0;
        for (int j = 0; j < tour.size() - 1; j++) {
            ConsumedFuel += fuelConsumptionMatrix[tour[j]][tour[j+1]];
        }
        ConsumedFuel++;
    return ConsumedFuel;
    }


};



class Ant{
public:
    Data& data;
    std::vector<int> path;
	std::set<int> available;
    double evaporationRate;
	double pheromoneMultiplier;     // importance of the pheromone level
	double visibilityMultiplier;    // importance of the visibility

    Ant(double pheromone, double visibility, double evaporationrate, Data& dataRef) : pheromoneMultiplier(pheromone), visibilityMultiplier(visibility), evaporationRate(evaporationrate),  data(dataRef) {
        path.push_back(0);
        for(int i = 1; i < data.n; i++) {
			available.insert(i);
		}
    }

    void reset() {
        std::vector<int> temp;
        temp.push_back(0);
        path = temp;
        for(int i = 1; i < data.n; i++) {
			available.insert(i);
		}
    }

    void setPheromones() {
        double fuelCost = data.tourCost(path);
        int depositAmount =  100;
        double pheromoneAmount = depositAmount / fuelCost;
        for (int i = 0; i < path.size() - 1; i++) {
            data.pheromoneMatrix[path[i]][path[i + 1]] += pheromoneAmount;
        }
        // data.pheromoneMatrix[path.back()][path.front()] += pheromoneAmount;
    }

    std::vector<int> trailEnd() {
        setPheromones();
        path.push_back(path[0]);
        std::vector<int> tem = path;
        reset();
        return tem;
    }

    void step() {
        int curCity = path[path.size() -1];
        double norm = 0.0;
        for (int city : available) {
            norm += pow(data.pheromoneMatrix[curCity][city], pheromoneMultiplier) * pow(data.visibilityMatrix[curCity][city], visibilityMultiplier);
        }

		double probability, randomProb;
		bool moved = false;
		double highestProb = 0;
		double cityHighest = 0;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);


        for(std::set<int>::iterator i=available.begin(); i != available.end(); i++) {
			probability = pow(data.pheromoneMatrix[curCity][*i], pheromoneMultiplier) * pow(data.visibilityMatrix[curCity][*i], visibilityMultiplier);
            probability /= norm;
			if (probability > highestProb) {
				cityHighest = *i;
				highestProb = probability;
			}


			randomProb = dis(gen);
			if (randomProb <= probability) { // move
				moved = true;
				path.push_back(*i);
				available.erase(i);
				break;
			}
		}
		if(!moved) {
			// make a move to the highest available prob city
			// move to cityHighest
			path.push_back(cityHighest);
			available.erase(cityHighest);
		}

    }

};



void HeuristicTSP::solveTSP() {
    Data data(cities, car);

    unsigned int noAnts = n*n;
    unsigned int noIterations = n;
    std::vector<Ant> ants;
    std::vector<int> bestSolutionTSP;
    Ant eliteAnts(pheromoneMultiplier, distanceMultiplier, n, data);
    double minTour = std::numeric_limits<double>::max();
    double tourCost = 0.0;

    for(int i = 0; i < noAnts; i++) {
			Ant a(pheromoneMultiplier, distanceMultiplier, n, data);
			ants.push_back(a);
		}

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for(int number = 0; number < noIterations; number++) {

		for(int p = 0; p < n; p++) {
			for(int i = 0; i < noAnts; i++) {
				ants[i].step();
			}
		}


			for(int i = 0; i < noAnts; i++) {

				std::vector<int> p = ants[i].trailEnd();

				if(!bestSolutionTSP.size()) {
					bestSolutionTSP = p;
					minTour = data.tourCost(p);
					continue;
				}
				tourCost = data.tourCost(p);
				if(tourCost < minTour) {
					minTour = tourCost;
					bestSolutionTSP = p;
				}
			}

            eliteAnts.path = bestSolutionTSP;
            eliteAnts.setPheromones();
            

			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					data.pheromoneMatrix[i][j] *= evaporationRate;
				}
			}
		}

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    for (int i = 0; i<n; i++) {
        std::cout << bestSolutionTSP[i] << "->";
    }
    std::cout << bestSolutionTSP[n] << "\nHeuristic: The consumed fuel using this route was: " << minTour<< std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    nlohmann::json jsonData;
    jsonData["route"] = bestSolutionTSP;

    std::ofstream outputFile("./solution/solutionHeuristic.json");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open json file." << std::endl;
        return;
    }
    outputFile << jsonData.dump(4);
    outputFile.close();
}