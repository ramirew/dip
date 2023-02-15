#ifndef SQUAREVARIANCE_H
#define SQUAREVARIANCE_H

#include <iostream>
#include <vector>

using namespace std;

class squarevariance;

class squarevariance
{
public:
    squarevariance();
    double f4_var (double **P, int Ng) const;
};

#endif
