#include "secondangular_p.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <omp.h>
using namespace std;
secondangular_p::secondangular_p(){}
//SUM VARIANCE
double secondangular_p::f1_asm (double **P, int Ng, int hilos) const{
    int i, j;
    double sum = 0;
#pragma omp parallel num_threads(hilos)
{
    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            sum += P[i][j] * P[i][j];
 }
    return sum;
}

