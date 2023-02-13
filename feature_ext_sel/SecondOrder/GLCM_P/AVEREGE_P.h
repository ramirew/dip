#ifndef AVEREGE_P_H
#define AVEREGE_P_H

#include <iostream>
#include <vector>

using namespace std;

class AVEREGE_P;

class AVEREGE_P
{
public:
    AVEREGE_P();
    double f6_savg (double **P, int Ng, int hilos) const;
};

#endif
