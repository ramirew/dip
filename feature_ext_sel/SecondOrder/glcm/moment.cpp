#include "moment.h"
#include <iostream>
#include <fstream>
#include <iostream>

using namespace std;
moment::moment(){}

//8 INVERSE DIFERENCE MOEMNT
double moment::f5_idm (double **P, int Ng) const {
    int i, j;
    double idm = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            idm += P[i][j] / (1 + (i - j) * (i - j));
    return idm;
}



