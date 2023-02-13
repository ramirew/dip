#ifndef SQUAREVARIANCE_P_H
#define SQUAREVARIANCE_P_H

#include <iostream>
#include <vector>

using namespace std;

class SQUAREVARIANCE_P;

class SQUAREVARIANCE_P
{
public:
    SQUAREVARIANCE_P();
    double f4_var (double **P, int Ng, int hilos) const;
};

#endif
