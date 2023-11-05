#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <string>

class Generator {
public:
    Generator();

    void generate(const std::string& fileName, unsigned int degree, int lConstraint, int rConstraint, unsigned int zDifference);
};

#endif