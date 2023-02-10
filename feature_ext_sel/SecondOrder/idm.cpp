#include "idm.h"
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

INDFM::INDFM()
{
}

/**
 * Método para calcular Inverse Difference Moment de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return idMoment value
 */
double INDFM::IM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double sum = 0;
    double idMoment = 0;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += pow(image[i][j],2);//stores the sum of the points
            idMoment += (1/(1+sum));//calculate Inverse Diferent Moment
        }
    }
    return idMoment;
}

/**
 * Método para calcular Inverse Difference Moment de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return idMoment value
 */
double INDFM::IM_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double sum = 0;
    double idMoment = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : idMoment)
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += pow(image[i][j],2);//stores the sum of the points
            idMoment += (1/(1+sum));//calculate Inverse Diferent Moment
        }
    }
    return idMoment;
}


