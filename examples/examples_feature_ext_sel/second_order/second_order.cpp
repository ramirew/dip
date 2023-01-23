#include <fstream>
#include <string.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>

// #include "SegundoOrden.h"
#include "dicom/DicomReader.h"
#include "SegundoOrden.h"

using namespace std;

vector<vector<int>> parseData(int **img, int size, int feat)
{
    std::vector<std::vector<int>> data;

    for (int i = 0; i < size; ++i)
    {
        std::vector<int> featureSet;
        for (int j = 0; j < feat; ++j)
        {
            featureSet.push_back(img[i][j]);
        }

        data.push_back(featureSet);
    }
    return data;
}

vector<int> generateLabels(int labelsSize)
{
    std::vector<int> labels;
    for (int i = 0; i < labelsSize; ++i)
    {
        int lbl = i % 4;
        labels.push_back(lbl);
    }
    return labels;
}

void saveData(vector<vector<int>> data, const char *filename)
{
    std::ofstream output_file(filename);

    for (const auto &row : data)
    {
        for (const auto &val : row)
        {
            output_file << val << ",";
        }
        output_file << "\n";
    }
}

void saveLabels(vector<int> labels)
{
    std::ofstream output_file("labels.csv");

    for (const auto &v : labels)
    {
        output_file << v << ",";
    }
}

int main(int argc, char *argv[])
{
    DicomReader dicomObj("/home/mpi-test/MasaMicro1.dcm");
    int size = dicomObj.getHeight();
    int elements = dicomObj.getWidth();

    vector<vector<int>> image = parseData(dicomObj.getImageArray(12), size, elements);

    SegundoOrden s;

    double idn = s.IDN(image);
    cout << "IDN: " << idn << endl;
    double ido_c4 = s.IDOC4(image);
    cout << "IDOC4: " << ido_c4 << endl;
    double inverse_variance = s.InverseVariance(image);
    cout << "InverseVariance: " << inverse_variance << endl;
    double local_homogeneity = s.LocalHomogeneity(image);
    cout << "LocalHomogeneity: " << local_homogeneity << endl;
    double lre = s.LRE(image);
    cout << "LRE: " << lre << endl;
    double max_probability = s.MaxProbability(image);
    cout << "MaxProbability: " << max_probability << endl;
    double max_intensityroi = s.MaxIntensityROI(image, 1000, 1000, 2000, 2000);
    cout << "MaxIntensityROI: " << max_intensityroi << endl;
    double mean_intensityroi = s.MeanIntensityROI(image, 1000, 1000, 2000, 2000);
    cout << "MeanIntensityROI: " << mean_intensityroi << endl;
    double mean_variance = s.MeanVariance(image);
    cout << "MeanVariance: " << mean_variance << endl;

    return 0;
}