#include "AbstractTSP.h"
#include "Car.h"
#include "City.h"

#include <vector>

AbstractTSP::AbstractTSP(std::vector<City> cities, Car car) : cities(cities), car(car) {}