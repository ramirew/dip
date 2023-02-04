#include "secondorder.h"
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

SecondOrder::SecondOrder()
{
}

/**
 * Método para calcular Inverse Difference Normalized utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Difference Normalized
 */
double SecondOrder::IDN(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();

    double IDN = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i + j != 0)
            {
                double p = (double)(image[i][j]) / (rows * cols);
                IDN += (1 / ((1 + ((i - j) * (i - j)) / (i + j)))) * p;
            }
        }
    }
    return IDN;
}

/**
 * Método para calcular Inverse Difference Normalized utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Difference Normalized
 */
double SecondOrder::IDN_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    unsigned i, j;
    double IDN = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for collapse(2) private(i, j) reduction(+ : IDN) 
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
          if (i + j != 0)
            {
                double p = (double)image[i][j] / (rows * cols);
                IDN += (1 / ((1 + ((i - j) * (i - j)) / (i + j)))) * p;

            }
        }
    }

    return IDN;
}
/**
 * Método para calcular Inverse Difference OC4 utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Difference OC4
 */
double SecondOrder::IDOC4(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();

    double IDOC4 = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i + j != 0)
            {
                IDOC4 += (1 / ((1 + ((i - j) * (i - j)) / (i + j)))) * (double)image[i][j];
            }
        }
    }

    return IDOC4;
}
/**
 * Método para calcular Inverse Difference OC4 utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Difference OC4
 */
double SecondOrder::IDOC4_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double IDOC4 = 0;
    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(+ \
                                               : IDOC4)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i + j != 0)
            {
                IDOC4 += (1 / ((1 + ((i - j) * (i - j)) / (i + j)))) * (double)image[i][j];
            }
        }
    }

    return IDOC4;
}

/**
 * Método para calcular Inverse Variance utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Variance
 */
double SecondOrder::InverseVariance(vector<vector<int>> image)
{
    double IV = 0;

    int rows = image.size();
    int cols = image[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols);
            IV += p / (1 + pow((i - j), 2));
        }
    }
    return IV;
}
/**
 * Método para calcular Inverse Variance utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Variance
 */
double SecondOrder::InverseVariance_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double IV = 0;
    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(+ \
                                               : IV)

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols);
            IV += p / (1 + pow((i - j), 2));
        }
    }


    return IV;
}

/**
 * Método para calcular Local Homogeneity utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Local Homogeneity
 */
double SecondOrder::LocalHomogeneity(vector<vector<int>> image)
{
    double LH = 0;

    int rows = image.size();
    int cols = image[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols);
            LH += p / (1 + ((i - j) * (i - j)) / (2));
        }
    }
    return LH;
}

/**
 * Método para calcular Local Homogeneity utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Local Homogeneity
 */
double SecondOrder::LocalHomogeneity_OPM(vector<vector<int>> image)
{
    double LH = 0;

    int rows = image.size();
    int cols = image[0].size();

    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(+ \
                                               : LH)
    for (int i = 0; i < rows; i++)
    {

        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols);
            LH += p / (1 + ((i - j) * (i - j)) / (2));
        }
    }
    return LH;
}

/**
 * Método para calcular la Maximum Probability utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Maximum Probability
 */
double SecondOrder::MaxProbability(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double maxProb = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols);
            maxProb = max(maxProb, p);
        }
    }
    return maxProb;
}

/**
 * Método para calcular la Maximum Probability utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Maximum Probability
 */
double SecondOrder::MaxProbability_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double maxProb = 0;
    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) schedule(dynamic) reduction(max \
                                                                 : maxProb)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols);
            maxProb = max(maxProb, p);
        }
    }
    return maxProb;
}

/**
 * Método para calcular el Maximum Value of Intensity en un área específica (ROI) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @param x1,y1 coordenadas x,y del punto inicial del ROI
 * @param x2,y2 coordenadas x,y del punto final del ROI
 * @return Maximum Value of Intensity en el ROI
 */
int SecondOrder::MaxIntensityROI(vector<vector<int>> image, int x1, int y1, int x2, int y2)
{
    int maxValue = INT_MIN;

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            {
                if (image[i][j] > maxValue)
                {
                    maxValue = image[i][j];
                }
            }
        }
    }

    return maxValue;
}

/**
 * Método para calcular el Maximum Value of Intensity en un área específica (ROI) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @param x1,y1 coordenadas x,y del punto inicial del ROI
 * @param x2,y2 coordenadas x,y del punto final del ROI
 * @return Maximum Value of Intensity en el ROI
 */

int SecondOrder::MaxIntensityROI_OPM(vector<vector<int>> image, int x1, int y1, int x2, int y2)
{
    int maxValue = INT_MIN;
    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(max \
                                               : maxValue)
    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            maxValue = max(maxValue, image[i][j]);
        }
    }
    return maxValue;
}
double SecondOrder::Mean(vector<vector<int>> image)
{
    int total_pixels = image.size() * image[0].size();
    int sum = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += (double)image[i][j];
        }
    }
    return (double)sum / total_pixels;
}

/**
 * Método para calcular el Mean Value of Intensity en un área específica (ROI) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @param x1,y1 coordenadas x,y del punto inicial del ROI
 * @param x2,y2 coordenadas x,y del punto final del ROI
 * @return Mean Value of Intensity en el ROI
 */
double SecondOrder::MeanIntensityROI(vector<vector<int>> image, int x1, int y1, int x2, int y2)
{
    double mean = 0;
    int count = 0;

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            mean += (double)image[i][j];
            count++;
        }
    }

    return mean / count;
}

/**
 * Método para calcular el Mean Value of Intensity en un área específica (ROI) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @param x1,y1 coordenadas x,y del punto inicial del ROI
 * @param x2,y2 coordenadas x,y del punto final del ROI
 * @return Mean Value of Intensity en el ROI
 */
double SecondOrder::MeanIntensityROI_OPM(vector<vector<int>> image, int x1, int y1, int x2, int y2)
{
    double mean = 0;
    int count = 0;
    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(+ \
                                               : mean, count)
    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            mean += (double)image[i][j];
            count++;
        }
    }

    return mean / count;
}

/**
 * Método para calcular Long Run Emphasis (LRE) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Long Run Emphasis (LRE)
 */
double SecondOrder::LRE(vector<vector<int>> image)
{
    double LRE = 0;
    int rows = image.size();
    int cols = image[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols); // probabilidad conjunta
            LRE += p * pow((i - j), 2);
        }
    }
    return LRE;
}

/**
 * Método para calcular Long Run Emphasis (LRE) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Long Run Emphasis (LRE)
 */
double SecondOrder::LRE_OPM(vector<vector<int>> image)
{
    double LRE = 0;

    int rows = image.size();
    int cols = image[0].size();

    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(+ \
                                               : LRE)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double p = (double)image[i][j] / (rows * cols); // probabilidad conjunta
            LRE += p * pow((i - j), 2);
        }
    }

    return LRE;
}

/**
 * Método para calcular el Mean Variance utilizando Second-Order Statistical
 * @param image vector de vectores de tipo int que representa la imagen DICOM
 * @return Mean Variance de la imagen
 */
double SecondOrder::MeanVariance(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double mean = 0;
    double variance = 0;
    double sum = 0;
    double sum2 = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mean += (double)image[i][j];
            sum += (i * (double)image[i][j]);
            sum2 += (i * i * (double)image[i][j]);
        }
    }
    mean = mean / (rows * cols);
    variance = sum2 / (rows * cols) - (sum / (rows * cols)) * (sum / (rows * cols));
    return variance;
}

/**
 * Método para calcular el Mean Variance utilizando Second-Order Statistical
 * @param image vector de vectores de tipo int que representa la imagen DICOM
 * @return Mean Variance de la imagen
 */
double SecondOrder::MeanVariance_OPM(vector<vector<int>> image)
{
    int rows = image.size();
    int cols = image[0].size();
    double mean = 0;
    double variance = 0;
    double sum = 0;
    double sum2 = 0;

    omp_set_num_threads(4);
#pragma omp parallel for collapse(2) reduction(+ \
                                               : mean, sum, sum2)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mean += (double)image[i][j];
            sum += (i * (double)image[i][j]);
            sum2 += (i * i * (double)image[i][j]);
        }
    }

    mean = mean / (rows * cols);
    variance = sum2 / (rows * cols) - (sum / (rows * cols)) * (sum / (rows * cols));
    return variance;
}
