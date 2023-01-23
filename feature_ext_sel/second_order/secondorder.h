#ifndef SECONDORDER_H
#define SECONDORDER_H
#include <stdio.h>
#include <vector>
using namespace std;
class SecondOrder
{
public:
  SecondOrder();
  void muestra_vector(const std::vector<int> &v);
  double IDN(vector<vector<int>> image);
  double IDN_OPM(vector<vector<int>> image);

  double IDOC4(vector<vector<int>> image);
  double IDOC4_OPM(vector<vector<int>> image);

  double InverseVariance(vector<vector<int>> image);
  double InverseVariance_OPM(vector<vector<int>> image);

  double LocalHomogeneity(vector<vector<int>> image);
  double LocalHomogeneity_OPM(vector<vector<int>> image);

  double LRE(vector<vector<int>> image);
  double LRE_ORM(vector<vector<int>> image);

  double MaxProbability(vector<vector<int>> image);
  double MaxProbability_OPM(vector<vector<int>> image);

  double MaxIntensityROI(vector<vector<int>> image, int x1, int y1, int x2, int y2);
  double MaxIntensityROI_OPM(vector<vector<int>> image, int x1, int y1, int x2, int y2);

  double MeanIntensityROI(vector<vector<int>> image, int x1, int y1, int x2, int y2);
  double MeanIntensityROI_OPM(vector<vector<int>> image, int x1, int y1, int x2, int y2);

  double MeanVariance(vector<vector<int>> image);
  double MeanVariance_OPM(vector<vector<int>> image);
  /*
    ?MEAN
    ?ROI
   */
  double Mean(vector<vector<int>> image);
  vector<vector<int>> ROI(vector<vector<int>> image, int x1, int y1, int x2, int y2);
};

#endif