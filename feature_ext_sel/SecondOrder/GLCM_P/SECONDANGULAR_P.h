#ifndef SECONDANGULAR_P_H
#define SECONDANGULAR_P_H

#include <iostream>
#include <vector>

using namespace std;

class SECONDANGULAR_P;

class SECONDANGULAR_P
{
public:
    SECONDANGULAR_P();
    double f1_asm (double **P, int Ng, int hilos) const;
};

#endif
