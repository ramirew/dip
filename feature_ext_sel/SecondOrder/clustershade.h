#ifndef CLUSTERSHADE_H
#define CLUSTERSHADE_H
#include <stdio.h>
#include <vector>
using namespace std;
class ClusterS
{
public:
  ClusterS();

  double CS(vector<vector<int>> image);
  double CS_OPM(vector<vector<int>> image);

};

#endif

