#include "globalmean.h"
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <omp.h>
#include <math.h>

using namespace std;

GBLM::GBLM()
{
}

/**
 * Método para calcular el Angular Second Moment de la imagen
 * @param image Matriz de la imagen
 * @param Pximg  Total Pixeles de la Imagen
 * @param sum Suma todos los Pixeles
 * @return gmean Global Mean de la imagen
 */
double GBLM::GM(vector<vector<int>> image)
{
    double gmean = 0;
    int Pximg = image.size() * image[0].size();
    int sum = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += (double)image[i][j];
        }
    }
    gmean = (double)sum / Pximg ;

    return gmean ;
}

/**
 * Método para calcular el Angular Second Moment de la imagen
 * @param image Matriz de la imagen
 * @param Pximg  Total Pixeles de la Imagen
 * @param sum Suma todos los Pixeles
 * @return gmean Global Mean de la imagen
 */
double GBLM::GM_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double gmean = 0;
    int Pximg = image.size() * image[0].size();
    int sum = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : gmean)
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += (double)image[i][j];
        }
    }
    gmean = (double)sum / Pximg ;

    return gmean ;
}


