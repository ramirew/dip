#ifndef DISSIMILARITY_H
#define DISSIMILARITY_H
#include <stdio.h>
#include <vector>
using namespace std;
class DISM
{
public:
  DISM();

  double DIS(vector<vector<int>> image);
  double DIS_OPM(vector<vector<int>> image);

};

#endif
