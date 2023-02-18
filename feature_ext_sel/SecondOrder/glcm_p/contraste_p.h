#ifndef CONTRASTE_P_H
#define CONTRASTE_P_H

#include <iostream>
#include <vector>

using namespace std;

class contraste_p;

class contraste_p
{
public:
    contraste_p();
    double f2_contrast (double **P, int Ng, int hilos) const;
};

#endif
