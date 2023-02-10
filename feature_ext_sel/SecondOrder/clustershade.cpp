#include "clustershade.h"
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

ClusterS::ClusterS()
{
}

/**
 * Método para calcular Cluster Shade de la imagen
 * @param arr matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return CSL value betwen 0-1
 */
double ClusterS::CS(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double avrg = 0;
	double sum = 0;
    double CLS = 0;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            avrg = sum/(rows*cols);//calculates the average
            CLS += pow((image[i][j]-avrg),3)/pow(10,17);//Calculate Cluster Shade
        }
    }
    return CLS;
}

/**
 * Método para calcular el Angular Second Moment de la imagen
 * @param image Matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return asm value betwen 0-1
 */
double ClusterS::CS_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double avrg = 0;
	double sum = 0;
    double CLS = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : CLS)
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            avrg = sum/(rows*cols);//calculates the average
            CLS += pow((image[i][j]-avrg),3)/pow(10,17);//Calculate Cluster Shade
        }
    }
    return CLS;
}

