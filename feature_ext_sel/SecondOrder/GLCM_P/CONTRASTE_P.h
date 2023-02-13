#ifndef CONTRASTE_P_H
#define CONTRASTE_P_H

#include <iostream>
#include <vector>

using namespace std;

class CONTRASTE_P;

class CONTRASTE_P
{
public:
    CONTRASTE_P();
    double f2_contrast (double **P, int Ng, int hilos) const;
};

#endif
