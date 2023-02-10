#ifndef DIAGONALMOMENT_H
#define DIAGONALMOMENT_H
#include <stdio.h>
#include <vector>
using namespace std;
class DiagonalM
{
public:
  DiagonalM();

  double DM(vector<vector<int>> image);
  double DM_OPM(vector<vector<int>> image);

};

#endif


