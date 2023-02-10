#include "uniformity.h"
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <climits>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <omp.h>
#include <math.h>

using namespace std;

Uniformity::Uniformity()
{
}

/**
 * Método para calcular la Uniformidad de la imagen
 * @param image Matriz de la imagen
 * @param Max ancho de la imagen
 * @param Min alto de la imagen
 * @return Uni value betwen 0-1
 */

double Uniformity::Ufm(vector<vector<int>> image)
{
   int Max = 500;
   int Min = 500;
   double Uni = 0;
   for (int i = 0; i < Min; ++i)//Traverse the matrix to obtain maximum and minimum points.
      {
            for (int j = 0; j < Max; ++j)
      {
       cout << image[i][j] << " ";
      }
    }
    Uni = 100 * ((Max-Min)/(Max+Min));//Calculate Uniformity

    return Uni;
}

/**
 * Método para calcular la Uniformidad de la imagen
 * @param image Matriz de la imagen
 * @param Max ancho de la imagen
 * @param min alto de la imagen
 * @return Uni value betwen 0-1
 */
double Uniformity::Ufm_OPM(vector<vector<int>> image)
{
    int Max = 500;
    int Min = 500;
    unsigned i, j;
    double Uni = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : Uni)
for (int i = 0; i < Min; ++i)//Traverse the matrix to obtain maximum and minimum points.
      {
    for (int j = 0; j < Max; ++j)
      {
       cout << image[i][j] << " ";
      }
    }
    Uni = 100 * ((Max-Min)/(Max+Min));//Calculate Uniformity

    return Uni;
}

