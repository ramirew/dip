#ifndef SQUAREVARIANCE_H
#define SQUAREVARIANCE_H

#include <iostream>
#include <vector>

/*
se define una clase "squarevariance" con un constructor y una función pública, pero no incluye su implementación. La implementación de la función "f4_var" 
se encuentra en el .cpp
*/
using namespace std;

class squarevariance;

class squarevariance
{
public:
    squarevariance();
    double f4_var (double **P, int Ng) const;
};

#endif
