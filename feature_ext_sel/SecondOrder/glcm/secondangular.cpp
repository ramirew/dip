#include "secondangular.h"
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
secondangular::secondangular(){}
//SUM VARIANCE
double secondangular::f1_asm (double **P, int Ng) const{
    int i, j;
    double sum = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            sum += P[i][j] * P[i][j];
    return sum;
}

