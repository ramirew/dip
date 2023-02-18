#ifndef CORRELATIONCOEFICIENT_H
#define CORRELATIONCOEFICIENT_H

#include <iostream>
#include <vector>

using namespace std;

class correlationcoeficient;

class correlationcoeficient
{
public:
    correlationcoeficient();
    double f14_maxcorr (double **P, int Ng) const;
    double f3_corr (double **P, int Ng) const ;
};

#endif
