#include "diagonalmoment.h"
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

DiagonalM::DiagonalM()
{
}

/**
 * Método para calcular Diagonal Moment de la imagen
 * @param image matriz de la imagen
 * @param cols ancho de la imagen
 * @param rows alto de la imagen
 * @return dM value between 0-1
 */

double DiagonalM::DM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
	double sum = 0;
    double dM = 0;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            dM += pow(sum,1/2)/pow(10,8);//Calculate Diagonal Moment
        }
    }
    return dM;
}


/**
 * Método para calcular Diagonal Moment de la imagen
 * @param image matriz de la imagen
 * @param cols ancho de la imagen
 * @param rows alto de la imagen
 * @return dM value between 0-1
 */

double DiagonalM::DM_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
	double sum = 0;
    double dM = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : dM)
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            dM += pow(sum,1/2)/pow(10,8);//Calculate Diagonal Moment
        }
    }
    return dM;
}


