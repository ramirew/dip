#ifndef IDM_H
#define IDM_H
#include <stdio.h>
#include <vector>
using namespace std;
class INDFM
{
public:
  INDFM();

  double IM(vector<vector<int>> image);
  double IM_OPM(vector<vector<int>> image);

};

#endif

