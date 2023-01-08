#ifndef ENTROPY_H
#define ENTROPY_H
#include <string>
#include <stdio.h>
#include <vector>

class Entropy
{
public:
  Entropy();
  int countlinesCSV(std::string nombre_archivo);
  double entropy(std::vector<int> histo,int width, int height , int index);
  std::vector<int> readCSV(std::string nombre_archivo);
};

#endif // ENTROPY_H
