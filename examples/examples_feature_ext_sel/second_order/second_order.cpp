#include <fstream>
#include <string.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>


#include "dicom_read/DicomReader.h"
#include "second_order/secondorder.h"

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

int main(int argc, char *argv[])
{
    DicomReader dicomObj("/home/evils/ups/paralela/test-opencv/images/MasaMicro1.dcm");
    int size = dicomObj.getHeight();
    int elements = dicomObj.getWidth();

    vector<vector<int>> image = parseData(dicomObj.getImageArray(12), size, elements);

    SecondOrder s;

    double idnP = s.IDN_OPM(image);
    cout << "IDN using OPM: " << idnP << endl;
    double idn = s.IDN(image);
    cout << "IDN: " << idn << endl;

    double ido_c4P = s.IDOC4_OPM(image);
    cout << "IDOC4 using OPM: " << ido_c4P << endl;
    double ido_c4 = s.IDOC4(image);
    cout << "IDOC4: " << ido_c4 << endl;

    double inverse_varianceP = s.InverseVariance_OPM(image);
    cout << "InverseVariance using OPM: " << inverse_varianceP << endl;
    double inverse_variance = s.InverseVariance(image);
    cout << "InverseVariance: " << inverse_variance << endl;

    double local_homogeneityP = s.LocalHomogeneity_OPM(image);
    cout << "LocalHomogeneity using OPM: " << local_homogeneityP << endl;
    double local_homogeneity = s.LocalHomogeneity(image);
    cout << "LocalHomogeneity: " << local_homogeneity << endl;

    double max_probabilityP = s.MaxProbability_OPM(image);
    cout << "MaxProbability using OPM: " << max_probabilityP << endl;
    double max_probability = s.MaxProbability(image);
    cout << "MaxProbability: " << max_probability << endl;

    double max_intensityroiP = s.MaxIntensityROI_OPM(image, 1000, 1000, 2000, 2000);
    cout << "MaxIntensityROI using OPM: " << max_intensityroiP << endl;
    double max_intensityroi = s.MaxIntensityROI(image, 1000, 1000, 2000, 2000);
    cout << "MaxIntensityROI: " << max_intensityroi << endl;

    double mean_intensityroiP = s.MeanIntensityROI_OPM(image, 1000, 1000, 2000, 2000);
    cout << "MeanIntensityROI using OPM: " << mean_intensityroiP << endl;
    double mean_intensityroi = s.MeanIntensityROI(image, 1000, 1000, 2000, 2000);
    cout << "MeanIntensityROI: " << mean_intensityroi << endl;

    double lreP = s.LRE_ORM(image);
    cout << "LRE using OPM: " << lreP << endl;
    double lre = s.LRE(image);
    cout << "LRE: " << lre << endl;

    double mean_varianceP = s.MeanVariance_OPM(image);
    cout << "MeanVariance using OPM: " << mean_varianceP << endl;
    double mean_variance = s.MeanVariance(image);
    cout << "MeanVariance: " << mean_variance << endl;

    return 0;
}