#ifndef FIRSTORDERCLASSIFIERSPARALLEL_H
#define FIRSTORDERCLASSIFIERSPARALLEL_H
#include <string>
#include <stdio.h>
#include <vector>

class FirstOrderClassifiersParallel
{
private:
  int threads;
public:
  FirstOrderClassifiersParallel();
  void muestra_vector(const std::vector<int>& v);
  std::vector<double> mean1(std::vector<std::vector<int>>arr,int type);
  std::vector<double> STD_VAR(std::vector<std::vector<int>>arr,int type);
  double Kurtosis(std::vector<std::vector<int>>arr,int flag);
  double Skewness(std::vector<std::vector<int>>arr,int flag);
  double MaxValue(std::vector<std::vector<int>>arr);
  double MinValue(std::vector<std::vector<int>>arr);
  void set_num_Threads(int threads);
};

#endif // FIRSTORDERCLASSIFIERSPARALLEL_H
