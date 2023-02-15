#ifndef SQUAREVARIANCE_P_H
#define SQUAREVARIANCE_P_H

#include <iostream>
#include <vector>

using namespace std;

class squarevariance_p;

class squarevariance_p
{
public:
    squarevariance_p();
    double f4_var (double **P, int Ng, int hilos) const;
};

#endif
