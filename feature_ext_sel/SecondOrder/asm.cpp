#include "asm.h"
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

Anglarsm::Anglarsm()
{
}

/**
 * Método para calcular el Angular Second Moment de la imagen
 * @param image Matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return asm value betwen 0-1
 */
double Anglarsm::Asm(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();

    double Asm = 0;
    for (int i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (int j = 0; j < cols; j++)
        {
            Asm += pow(image[i][j],2)/pow(10,14);
        }
    }
    return Asm;
}

/**
 * Método para calcular el Angular Second Moment de la imagen
 * @param image Matriz de la imagen
 * @param rows ancho de la imagen
 * @param cols alto de la imagen
 * @return asm value betwen 0-1
 */
double Anglarsm::Asm_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double Asm = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : Asm)
    for (i = 0; i < rows; i++)//Go through the Matrix to analyze each point.
    {
        for (j = 0; j < cols; j++)
        {
            for (int j = 0; j < cols; j++)
            {
                Asm += pow(image[i][j],2)/pow(10,14);//Calculate Asm
            }
        }
    }
    return Asm;
}

