#include "dissimilarity.h"
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

DISM::DISM()
{
}

/**
 * Método para calcular Dissimilarity de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return disM value between 0-1
 */

double DISM::DIS(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double sbtr = 0;
    double disM;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sbtr = rows - cols;//stores the subtraction of the points
            disM += image[i][j] * (sbtr) /pow(10,13);//Calculate dissimilarity
        }
    }
    return disM;
}

/**
 * Método para calcular el Angular Second Moment de la imagen
 * @param image Matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return asm value betwen 0-1
 */
double DISM::DIS_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double sbtr = 0;
    double disM;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : disM)
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sbtr = rows - cols;//stores the subtraction of the points
            disM += image[i][j] * (sbtr) /pow(10,13);//Calculate dissimilarity
        }
    }
    return disM;
}


