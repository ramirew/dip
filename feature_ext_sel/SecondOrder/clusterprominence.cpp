#include "clusterprominence.h"
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

ClusterP::ClusterP()
{
}

/**
 * Método para calcular Cluster Prominence de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return CLP value betwen 0-1
 */

double ClusterP::CP(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double sum = 0;
    double avrg = 0;
    double CLP = 0;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            avrg = sum/(rows*cols);//calculates the average
            CLP += pow((image[i][j]- avrg),4)/pow(10,20);//Calculate Cluster Prominence
        }
    }
    return CLP;
}

/**
 * Método para calcular Cluster Prominence de la imagen
 * @param image matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return CLP value betwen 0-1
 */
double ClusterP::CP_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double sum = 0;
    double avrg = 0;
    double CLP = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : CLP)
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            sum += image[i][j];//stores the sum of the points
            avrg = sum/(rows*cols);//calculates the average
            CLP += pow((image[i][j]- avrg),4)/pow(10,20);//Calculate Cluster Prominence
        }
    }
    return CLP;
}


