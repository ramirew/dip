#ifndef FIRSTORDERCLASSIFIERS_H
#define FIRSTORDERCLASSIFIERS_H
#include <string>
#include <stdio.h>
#include <vector>

class FirstOrderClassifiers
{
public:
  FirstOrderClassifiers();
  void muestra_vector(const std::vector<int>& v);
  std::vector<double> mean1(std::vector<std::vector<int>>arr,int type);
  std::vector<double> STD_VAR(std::vector<std::vector<int>>arr,int type);
  double Kurtosis(std::vector<std::vector<int>>arr,int flag);
  double Skewness(std::vector<std::vector<int>>arr,int flag);
  double MaxValue(std::vector<std::vector<int>>arr);
  double MinValue(std::vector<std::vector<int>>arr);
};

#endif // FIRSTORDERCLASSIFIERS_H
