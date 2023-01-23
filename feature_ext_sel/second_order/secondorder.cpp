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
#include <math.h>

using namespace std;

SecondOrder::SecondOrder()
{
}

void SecondOrder::muestra_vector(const vector<int> &v)
{
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}

/**
 * Método para calcular Inverse Difference Normalized utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Inverse Difference Normalized
 */
double SecondOrder::IDN(vector<vector<int>> image)
{
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Inverse Difference Normalized utilizando la matriz de probabilidad conjunta
    double IDN = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            if (i + j != 0)
            {
                IDN += (1 / ((1 + ((i - j) * (i - j)) / (i + j)))) * jointProbHist[i][j];
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
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Inverse Difference OC4 utilizando la matriz de probabilidad conjunta
    double IDOC4 = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            if (i + j != 0)
            {
                IDOC4 += pow((i - j) / (i + j), 4) * jointProbHist[i][j];
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
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Inverse Variance utilizando la matriz de probabilidad conjunta
    double mean = 0;
    double variance = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            mean += i * jointProbHist[i][j];
            variance += (i - mean) * (i - mean) * jointProbHist[i][j];
        }
    }
    return 1 / variance;
}

/**
 * Método para calcular Local Homogeneity utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Local Homogeneity
 */
double SecondOrder::LocalHomogeneity(vector<vector<int>> image)
{
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Local Homogeneity utilizando la matriz de probabilidad conjunta
    double homogeneity = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            if (jointProbHist[i][j] > 0)
            {
                homogeneity += jointProbHist[i][j] / (1 + (i - j) * (i - j));
            }
        }
    }
    return homogeneity;
}

/**
 * Método para calcular la Maximum Probability utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Maximum Probability
 */
double SecondOrder::MaxProbability(vector<vector<int>> image)
{
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Maximum Probability utilizando la matriz de probabilidad conjunta
    double maxProb = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            if (jointProbHist[i][j] > maxProb)
            {
                maxProb = jointProbHist[i][j];
            }
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
double SecondOrder::MaxIntensityROI(vector<vector<int>> img, int x1, int y1, int x2, int y2)
{
    int pixelCount = img.size() * img[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                   // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = y1; i <= y2; i++)
    {
        for (int j = x1; j <= x2; j++)
        {
            jointProbHist[img[i][j]][img[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Maximum Value of Intensity en el ROI utilizando la matriz de probabilidad conjunta
    double Max = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            if (jointProbHist[i][j] > Max)
            {
                Max = jointProbHist[i][j];
            }
        }
    }
    return Max;
}

double SecondOrder::Mean(vector<vector<int>> image)
{
    int total_pixels = image.size() * image[0].size();
    int sum = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            sum += image[i][j];
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
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = y1; i <= y2; i++)
    {
        for (int j = x1; j <= x2; j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Mean Value of Intensity en el ROI utilizando la matriz de probabilidad conjunta
    double Mean = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            Mean += (i + j) * jointProbHist[i][j];
        }
    }
    return Mean;
}

/**
 * Método para extraer la región de interés (ROI) en una imagen representada en un vector de vectores de tipo int
 * @param image vector de vectores de tipo int que representa la imagen
 * @param x1 coordenada x1 de la ROI
 * @param y1 coordenada y1 de la ROI
 * @param x2 coordenada x2 de la ROI
 * @param y2 coordenada y2 de la ROI
 * @return vector de vectores de tipo int con los valores de los píxeles dentro de la ROI
 */

vector<vector<int>> SecondOrder::ROI(vector<vector<int>> image, int x1, int y1, int x2, int y2)
{
    vector<vector<int>> roi_image;
    for (int i = x1; i <= x2; i++)
    {
        vector<int> row;
        for (int j = y1; j <= y2; j++)
        {
            row.push_back(image[i][j]);
        }
        roi_image.push_back(row);
    }
    return roi_image;
}

/**
 * Método para calcular Long Run Emphasis (LRE) utilizando Second-Order Statistical
 * @param img vector de vectores de tipo int que representa la imagen DICOM
 * @return Long Run Emphasis (LRE)
 */
double SecondOrder::LRE(vector<vector<int>> img)
{
    int pixelCount = img.size() * img[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                   // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < img.size(); i++)
    {
        for (int j = 0; j < img[0].size(); j++)
        {
            jointProbHist[img[i][j]][img[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Long Run Emphasis (LRE) utilizando la matriz de probabilidad conjunta
    double LRE = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            LRE += pow(i - j, 2) * jointProbHist[i][j];
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
    int pixelCount = image.size() * image[0].size(); // total de pixeles de la imagen
    int intensityRange = 4096;                       // rango de intensidad de la imagen

    // Crear la matriz de probabilidad conjunta
    vector<vector<double>> jointProbHist(intensityRange, vector<double>(intensityRange, 0));
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[0].size(); j++)
        {
            jointProbHist[image[i][j]][image[i][j]]++;
        }
    }
    // normalizar la matriz de probabilidad conjunta
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            jointProbHist[i][j] /= pixelCount;
        }
    }
    // Calcular Mean utilizando la matriz de probabilidad conjunta
    double Mean = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            Mean += i * j * jointProbHist[i][j];
        }
    }
    // Calcular Variance utilizando la matriz de probabilidad conjunta y el Mean
    double Variance = 0;
    for (int i = 0; i < intensityRange; i++)
    {
        for (int j = 0; j < intensityRange; j++)
        {
            Variance += (i - Mean) * (i - Mean) * jointProbHist[i][j];
        }
    }
    // Calcular Mean Variance utilizando Mean y Variance
    double MeanVariance = Mean - Variance;
    return MeanVariance;
}
