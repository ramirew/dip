#ifndef ENTROPYPARALLEL_H
#define ENTROPYPARALLEL_H
#include <string>
#include <stdio.h>
#include <vector>

class EntropyParallel
{
private:
  int threads;
public:
  EntropyParallel();
  int countlinesCSV(std::string nombre_archivo);
  double entropy(std::vector<int> histo,int width, int height , int index);
  std::vector<int> readCSV(std::string nombre_archivo);
  void set_num_threads(int th);
};

#endif // ENTROPYPARALLEL_H
