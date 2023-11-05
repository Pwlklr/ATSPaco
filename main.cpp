#include "City.h"
#include "Car.h"
#include "Generator.h"
#include "AbstractTSP.h"
#include "GreedyTSP.h"
#include "RandomisedGreedyTSP.h"
#include "BruteForceTSP.h"
#include "HeuristicTSP.h"


#include "nlohmann/json.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <direct.h>
#include <chrono>


int main() {

    if (_chdir("D:/Studia/Semestr_3/OptymalizacjaKombinatoryczna/projekt/") != 0) { //change to current folder
        std::cerr << "Unable to change workfolder" << std::endl;
        return 1;
    }

    std::ifstream dataFile;
    char response;
    std::string name;
    float fuelConsumption;
    
    //INTERACTIVE PART
    std::cout << "Do you want to generate a data file and use it? (y/n)" << std::endl;
    std::cin >> response;
    if (response == 'y') {
        std::string filename;
        unsigned int n, z;
        int lConstraint, rConstraint;
        Generator genarator;
        std::cout << "\nInput filename, number of cities, lConstraint, rConstraint and max z values." << std::endl;
        std::cin >> filename >> n >> lConstraint >> rConstraint >> z;
        genarator.generate(filename, n, lConstraint, rConstraint, z);    //GENERATOR
        
        name = "./data/" + filename + ".json";
        dataFile.open(name); //File to be put inside cities vector
    }
    else if (response == 'n') {
        std::cout << "\nInput filename that you wish to use." << std::endl;
        std::string filename;
        std::cin >> filename;
        name = "./data/" + filename + ".json";
        dataFile.open(name); //File to be put inside cities vector
    }
    else {std::cout << "Wrong command" << std::endl; return 1;}
    

    if (!dataFile.is_open()) {
        std::cerr << "Unable to open JSON file." << std::endl;
        return 1;
    }

    nlohmann::json data;
    dataFile >> data;
    dataFile.close();

    std::vector<City> cities;

    for (const auto& cityData : data) {
        City city(cityData["id"], cityData["x"], cityData["y"], cityData["z"]);
        cities.push_back(city);
    }

    std::cout << "\nDo you want to print the cities? (y/n)" << std::endl;
    std::cin >> response;
    if (response == 'y') {
        for (const City& city : cities) {
            std::cout << "City: " << city.getId() << " (x=" << city.getX() << ", y=" << city.getY() << ", z=" << city.getZ() << ")" << std::endl;
        }
    }

    std::cout << "\nInput data about the car. (name, avgFuelConsumption/100km)" << std::endl;
    std::cin >> name >> fuelConsumption;

    Car car(name, fuelConsumption);
    char response1, response2, response3, response4;
    std::cout << "\nChoose which algorithms do you wish to use:\nGreedy (y/n)\nRandomised greedy (y/n)\nBrute Force (!USE ONLY FOR SMALL INSTANCES OF THE PROBLEM!) (y/n)\nAnt colony (y/n)" << std::endl;
    std::cin >> response1 >> response2 >> response3 >> response4;

    if (response1 == 'y') {
        GreedyTSP solver1(cities, car);

        std::cout << "\nWhich greedy approach do you wish to use? \n1->default\n2->specify the starting city\n3->test all starting cities\n4->option 1 and 2" << std::endl;
        std::cin >> response1;
        if(response1 == '1') {
            std::cout << "SOLUTION:" << std::endl;
            solver1.solveTSP();
        }
        else if(response1 == '2') {
            unsigned int chosenCity;
            std::cout << "\nInput the starting city:" << std::endl;
            std::cin >> chosenCity;
            if (chosenCity > cities.size()) {std::cout << "Incorrect staring city" << std::endl; return 1;}
            std::cout << "SOLUTION:" << std::endl;
            solver1.solveTSP(chosenCity);
        }
        else if(response1 == '3') {
            std::cout << "SOLUTION:" << std::endl;
            solver1.solveTSPAC();
        }
        else if (response1 == '4') {
            std::cout << "SOLUTION:" << std::endl;
            solver1.solveTSP();
            std::cout << "\n\n";
            std::cout << "SOLUTION:" << std::endl;
            solver1.solveTSPAC();
        }
        else {std::cout << "Wrong command" << std::endl; return 1;}
        std::cout << "\n\n\n";
    }

    if (response2 == 'y') {
        RandomisedGreedyTSP solver2(cities, car);
        std::cout << "SOLUTION:" << std::endl;
        solver2.solveTSP();
        std::cout << "\n\n\n";
    }

    if (response3 == 'y') {
        BruteForceTSP solver3(cities, car);
        std::cout << "SOLUTION:" << std::endl;
        solver3.solveTSP();
        std::cout << "\n\n\n";
    }

    if (response4 == 'y') {
        double pheromoneMultiplier, distanceMultiplier, evaporationRate;
        std::cout << "\nInput pheromone multiplier, visibility multiplier and evaporation rate [0,1]" << std::endl;
        std::cin >> pheromoneMultiplier >> distanceMultiplier >> evaporationRate;
        HeuristicTSP solver4(cities, car, pheromoneMultiplier, distanceMultiplier, evaporationRate);
        std::cout << "SOLUTION:" << std::endl;
        solver4.solveTSP();
        std::cout << "\n\n\n";
    }




    /*
    Usage from code, without UI
    To use uncomment all lines below and comment all lines above
    */

    // nlohmann::json data;

    // dataFile.open("./data/generatedData30.json");

    // dataFile >> data;
    // dataFile.close();
    // Car car("tst", 18);
    // std::vector<City> cities;

    // for (const auto& cityData : data) {
    //     City city(cityData["id"], cityData["x"], cityData["y"], cityData["z"]);
    //     cities.push_back(city);
    // }

    // GreedyTSP solver1(cities, car);
    // RandomisedGreedyTSP solver2(cities, car);
    // BruteForceTSP solver3(cities, car);
    // HeuristicTSP solver4(cities, car, 5, 5, 0.8); //Pheromone multiplier, visibility multiplier, evaporationRate [0,1] (the higher the slower it evaporates)



    // solver1.solveTSP();

    // std::cout << "\n\n\n";

    // solver1.solveTSPAC();

    // std::cout << "\n\n\n";

    // solver2.solveTSP();

    // std::cout << "\n\n\n";

    // // solver3.solveTSP(); //Comment to disable bruteForce

    // // std::cout << "\n\n\n";

    // solver4.solveTSP();


    return 0;
}