#include "contraste.h"
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
contraste::contraste(){}
//7 CONTRASTE

/*
define una función llamada "f2_contrast" dentro de la clase "contraste".
La función "f2_contrast" calcula el contraste de una matriz de tamaño NgxNg representada por la matriz P.
*/
double contraste::f2_contrast (double **P, int Ng) const {
    int i, j, n;
    double sum = 0, bigsum = 0;
    for (n = 0; n < Ng; ++n) {
        for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j) {
                if ((i - j) == n || (j - i) == n)
                    sum += P[i][j];
                }
        bigsum += n * n * sum;
        sum = 0;
    }
    return bigsum;
}

