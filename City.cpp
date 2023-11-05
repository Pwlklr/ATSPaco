#include "City.h"

City::City(int _id, float _x, float _y, float _z) : id(_id), x(_x), y(_y), z(_z) {}

int City::getId() const {
    return id;
}

double City::getX() const {
    return x;
}

double City::getY() const {
    return y;
}  

double City::getZ() const {
    return z;
}