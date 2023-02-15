#ifndef ENTROPIA_P_H
#define ENTROPIA_P_H

#include <iostream>
#include <vector>

using namespace std;

class entropia_p;

class entropia_p
{
public:
    entropia_p();
    double f8_sentropy (double **P, int Ng, int hilos) const;
    double f9_entropy (double **P, int Ng, int hilos) const;
    double f11_dentropy (double **P, int Ng, int hilos) const;
};

#endif
