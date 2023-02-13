#ifndef CORRELATIONCOEFICIENT_P_H
#define CORRELATIONCOEFICIENT_P_H

#include <iostream>
#include <vector>

using namespace std;

class CORRELATIONCOEFICIENT_P;

class CORRELATIONCOEFICIENT_P
{
public:
    CORRELATIONCOEFICIENT_P();
    double f14_maxcorr (double **P, int Ng, int hilos) const;
    double f3_corr (double **P, int Ng, int hilos) const ;
};

#endif
