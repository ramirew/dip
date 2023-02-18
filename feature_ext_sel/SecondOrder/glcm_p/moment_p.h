#ifndef MOEMNT_P_H
#define MOEMNT_P_H

#include <iostream>
#include <vector>

using namespace std;

class moment_p;

class moment_p
{
public:
    moment_p();
    double f5_idm (double **P, int Ng, int hilos) const;
};

#endif
