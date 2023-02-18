#ifndef SECONDANGULAR_P_H
#define SECONDANGULAR_P_H

#include <iostream>
#include <vector>

using namespace std;

class secondangular_p;

class secondangular_p
{
public:
    secondangular_p();
    double f1_asm (double **P, int Ng, int hilos) const;
};

#endif
