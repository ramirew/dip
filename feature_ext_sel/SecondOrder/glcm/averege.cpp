#include "averege.h"
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
averege::averege(){}

//RECURSOS DE LOS METODOS
double *allocate_vector (int nl, int nh);

//4 SUM AVEREGE
double averege::f6_savg (double **P, int Ng) const {
    int i, j;
    double savg = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);

    for (i = 0; i <= 2 * Ng; ++i)
        Pxpy[i] = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
          Pxpy[i + j] += P[i][j];

    for (i = 0; i <= (2 * Ng - 2); ++i)
        savg += i * Pxpy[i];

    free (Pxpy);
    return savg;
}

