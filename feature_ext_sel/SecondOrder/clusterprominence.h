#ifndef CLUSTERPROMINENCE_H
#define CLUSTERPROMINENCE_H
#include <stdio.h>
#include <vector>
using namespace std;
class ClusterP
{
public:
 ClusterP();

  double CP(vector<vector<int>> image);
  double CP_OPM(vector<vector<int>> image);

};

#endif

