#ifndef AVEREGE_P_H
#define AVEREGE_P_H

#include <iostream>
#include <vector>

using namespace std;

class averege_p;

class averege_p
{
public:
    averege_p();
    double f6_savg (double **P, int Ng, int hilos) const;
};

#endif
