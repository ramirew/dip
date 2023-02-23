#include "averege_p.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <omp.h>
using namespace std;
averege_p::averege_p(){}

//RECURSOS DE LOS METODOS
double *allocate_vector (int nl, int nh);
//4 SUM AVEREGE
double averege_p::f6_savg (double **P, int Ng, int hilos) const {
    int i, j;
    double savg = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);

    #pragma omp parallel num_threads(hilos)
        {
        //int hilo = omp_get_thread_num();
        for (i = 0; i <= 2 * Ng; ++i)
            Pxpy[i] = 0;

        for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j)
              Pxpy[i + j] += P[i][j];

        for (i = 0; i <= (2 * Ng - 2); ++i)
            savg += i * Pxpy[i];
        savg = 222;
    }
    free (Pxpy);
    return savg;
}

