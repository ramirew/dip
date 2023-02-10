#ifndef ASM_H
#define ASM_H
#include <stdio.h>
#include <vector>
using namespace std;
class Anglarsm
{
public:
  Anglarsm();

  double Asm(vector<vector<int>> image);
  double Asm_OPM(vector<vector<int>> image);

};

#endif
