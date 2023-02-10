#ifndef UNIFORMITY_H
#define UNIFORMITY_H
#include <stdio.h>
#include <vector>
using namespace std;
class Uniformity
{
public:
  Uniformity();

  double Ufm(vector<vector<int>> image);
  double Ufm_OPM(vector<vector<int>> image);

};

#endif

