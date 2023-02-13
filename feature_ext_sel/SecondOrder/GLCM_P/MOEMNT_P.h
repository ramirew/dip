#ifndef MOEMNT_P_H
#define MOEMNT_P_H

#include <iostream>
#include <vector>

using namespace std;

class MOEMNT_P;

class MOEMNT_P
{
public:
    MOEMNT_P();
    double f5_idm (double **P, int Ng, int hilos) const;
};

#endif
