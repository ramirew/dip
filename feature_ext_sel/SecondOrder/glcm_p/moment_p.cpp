#include "moment_p.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <omp.h>

using namespace std;
moment_p::moment_p(){}

//8 INVERSE DIFERENCE MOEMNT
double moment_p::f5_idm (double **P, int Ng, int hilos) const {
    int i, j;
    double idm = 0;
#pragma omp parallel num_threads(hilos)
{
    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            idm += P[i][j] / (1 + (i - j) * (i - j));
 }
    return idm;
}



