#ifndef INTERNALVARIANCE_H
#define INTERNALVARIANCE_H
#include <stdio.h>
#include <vector>
using namespace std;
class INV
{
public:
  INV();

  double INVAR(vector<vector<int>> image);
  double INVAR_OPM(vector<vector<int>> image);

};

#endif

