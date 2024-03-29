#include "contraste_p.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <omp.h>
using namespace std;
contraste_p::contraste_p(){}
//7 CONTRASTE
double contraste_p::f2_contrast (double **P, int Ng, int hilos) const {
    int i, j, n;
    double sum = 0, bigsum = 0;
    #pragma omp parallel num_threads(hilos)
    {
        for (n = 0; n < Ng; ++n) {
            for (i = 0; i < Ng; ++i)
                for (j = 0; j < Ng; ++j) {
                    if ((i - j) == n || (j - i) == n)
                        sum += P[i][j];
                    }
            bigsum += n * n * sum;
            sum = 0;
        }
    }
    return bigsum;
}

