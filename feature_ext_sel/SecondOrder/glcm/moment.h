#ifndef MOEMNT_H
#define MOEMNT_H

#include <iostream>
#include <vector>

using namespace std;

class moment;

class moment
{
public:
    moment();
    double f5_idm (double **P, int Ng) const;
};

#endif
