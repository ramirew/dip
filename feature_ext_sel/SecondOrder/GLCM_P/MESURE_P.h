#ifndef MESURE_P_H
#define MESURE_P_H

#include <iostream>
#include <vector>

using namespace std;

class MESURE_P;

class MESURE_P
{
public:
    MESURE_P();
    double f12_icorr (double **P, int Ng, int hilos) const;
    double f13_icorr (double **P, int Ng, int hilos) const;
};

#endif
