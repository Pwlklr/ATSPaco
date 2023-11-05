#ifndef _CITY_H_
#define _CITY_H_

class City {
private:
    double x;
    double y;
    double z;
    unsigned int id;

public:
    City(int _id, float _x, float _y, float _z);
    int getId() const;
    double getX() const;
    double getY() const;
    double getZ() const;

};
#endif