#include "internalvariance.h"
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

INV::INV()
{
}

/**
 * Método para calcular Internal Variance de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return ivariance value between 0-1
 */

double INV::INVAR(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double avrg = 0;
    double sum = 0;
    double ivariance;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            avrg = sum/(rows*cols);
            ivariance += pow((image[i][j]-avrg),2)/pow(10,13);//calculate Internal Variance of the image
        }
    }
    return ivariance;
}

/**
 * Método para calcular Internal Variance de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return ivariance value between 0-1
 */
double INV::INVAR_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double avrg = 0;
    double sum = 0;
    double ivariance;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : ivariance)
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            avrg = sum/(rows*cols);
            ivariance += pow((image[i][j]-avrg),2)/pow(10,13);//calculate Internal Variance of the image
        }
    }
    return ivariance;
}


