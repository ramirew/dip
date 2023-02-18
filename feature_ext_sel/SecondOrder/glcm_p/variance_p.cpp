#include "variance_p.h"
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
variance_p::variance_p(){}
double *allocate_vector (int nl, int nh);
//SUM variance_p
double variance_p::f7_svar (double **P, int Ng, double S, int hilos) const {
    int i, j;
    double var = 0;
    double *Pxpy = allocate_vector(0, 2*Ng);

    for (i = 0; i <= 2 * Ng; ++i)
        Pxpy[i] = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
          Pxpy[i + j] += P[i][j];

    for (i = 0; i <= (2 * Ng - 2); ++i)
        var += (i - S) * (i - S) * Pxpy[i];

    free (Pxpy);
    return var;
}

//10 DIFERENCIA VARIANZA
double variance_p::f10_dvar (double **P, int Ng, int hilos) const {
    int i, j;
    double sum = 0, sum_sqr = 0, var = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);

    for (i = 0; i <= 2 * Ng; ++i)
        Pxpy[i] = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            Pxpy[abs (i - j)] += P[i][j];

    for (i = 0; i < Ng; ++i) {
        sum += i * Pxpy[i] ;
        sum_sqr += i * i * Pxpy[i] ;
    }
    var = sum_sqr - sum*sum ;
    free (Pxpy);
    return var;
}



