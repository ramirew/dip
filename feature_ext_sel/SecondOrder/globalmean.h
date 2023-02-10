#ifndef GLOBALMEAN_H
#define GLOBALMEAN_H
#include <stdio.h>
#include <vector>
using namespace std;
class GBLM
{
public:
  GBLM();

  double GM(vector<vector<int>> image);
  double GM_OPM(vector<vector<int>> image);

};

#endif
