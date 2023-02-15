#ifndef SQUAREVARIANCE_P_H
#define SQUAREVARIANCE_P_H

#include <iostream>
#include <vector>

/*
se define una clase "squarevariance" con un constructor y una función pública, pero no incluye su implementación. 
La implementación de la función "f4_var" se encuentra en el .cpp
*/

using namespace std;

class squarevariance_p;

class squarevariance_p
{
public:
    squarevariance_p();
    double f4_var (double **P, int Ng, int hilos) const;
};

#endif
