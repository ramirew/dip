#ifndef VARIANCE_P_H
#define VARIANCE_P_H

#include <iostream>
#include <vector>

using namespace std;

class variance_p;

class variance_p
{
public:
    variance_p();
    double f7_svar(double **P, int Ng, double S, int hilos) const;
    double f10_dvar (double **P, int Ng, int hilos) const;
};

#endif
