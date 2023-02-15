#ifndef MESURE_P_H
#define MESURE_P_H

#include <iostream>
#include <vector>

using namespace std;

class mesure_p;

class mesure_p
{
public:
    mesure_p();
    double f12_icorr (double **P, int Ng, int hilos) const;
    double f13_icorr (double **P, int Ng, int hilos) const;
};

#endif
