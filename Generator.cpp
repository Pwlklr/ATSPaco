#include "Generator.h"

#include "nlohmann/json.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>
#include <cmath>


Generator::Generator() {}

void Generator::generate(const std::string& filename, unsigned int degree, int lConstraint, int rConstraint, unsigned int zDifference) {

    nlohmann::json generatedDataArray;

    if (lConstraint > rConstraint) {
        std::swap(lConstraint, rConstraint);
        std::cout << "Left constraint was larger than the right one. Swapped, continuing..." << std::endl;
    }


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(lConstraint, rConstraint);
    std::uniform_int_distribution<int> distZ(0, zDifference);


    for (int i=0; i<degree; i++) {
        nlohmann::json generatedData;
        generatedData["id"] = i;
        generatedData["x"] = dist(gen);
        generatedData["y"] = dist(gen);
        generatedData["z"] = distZ(gen);

        generatedDataArray.push_back(generatedData);
    }

    std::string filePath = "./data/" + filename + ".json"; // Utworzenie pełnej ścieżki dostępu z nazwą pliku
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open JSON file." << std::endl;
        return;
    }
    file << generatedDataArray.dump(4);
    file.close();

}