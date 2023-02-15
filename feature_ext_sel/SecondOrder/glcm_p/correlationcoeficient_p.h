#ifndef CORRELATIONCOEFICIENT_P_H
#define CORRELATIONCOEFICIENT_P_H

#include <iostream>
#include <vector>

using namespace std;

class correlationcoeficient_p;

class correlationcoeficient_p
{
public:
    correlationcoeficient_p();
    double f14_maxcorr (double **P, int Ng, int hilos) const;
    double f3_corr (double **P, int Ng, int hilos) const ;
};

#endif
