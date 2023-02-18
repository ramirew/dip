#ifndef MESURE_H
#define MESURE_H

#include <iostream>
#include <vector>

using namespace std;

class mesure;

class mesure
{
public:
    mesure();
    double f12_icorr (double **P, int Ng) const;
    double f13_icorr (double **P, int Ng) const;
};

#endif
