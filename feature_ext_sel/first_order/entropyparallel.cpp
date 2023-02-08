#include "entropyparallel.h"
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

EntropyParallel::EntropyParallel()
{
  this->threads = 3;
}

void EntropyParallel::set_num_threads(int th){
  this -> threads = th;
}

/**
 * Metodo para leer el vector escrito en el CSV
 * @param nombre_archivo
 * @return vector con los datos escritos en el archivo CSV
 */
vector<int> EntropyParallel::readCSV(string nombre_archivo)
{
  int valor;
  vector<int> datos;
  ifstream fich(nombre_archivo);
  if (!fich)
  {
    cout<< "ERROR"<<endl;
  }
  else
  {
    while(fich >> valor)
    {
      datos.push_back(valor);
    }
  }
  fich.close();
  return datos;
}

/**
 * Metodo para la longitud del vector almacenado en el archivo CSV
 * @param nombre_archivo
 * @return número de lineas en el archivo CSV
 */
int EntropyParallel::countlinesCSV(string nombre_archivo)
{
  ifstream archivo(nombre_archivo);
  string linea;
  int num_lineas = 0;
  while(getline(archivo,linea)){
      num_lineas ++;
  }
  archivo.close();
  return num_lineas;
}

/**
 * Método para calcular la entropia una imagen
 * @param seq histograma de la imagen
 * @param width ancho de la imagen
 * @param height alto de la imagemn
 * @param index total de pixeles dado la profundidad de la imagen
 * @return entropy value
 */
double EntropyParallel::entropy(vector<int> histo,int width, int height , int index)
{
  int cnt = 0;
  double entr = 0;
  float total_size = height * width; //total size of all symbols in an image
    omp_set_num_threads(this->threads);
    #pragma omp parallel for reduction(+: entr)
    for(int i=0;i<index;i++)
    {
      double sym_occur = histo[i]; //the number of times a sybmol has occured
      if(sym_occur>0) //log of zero goes to infinity
        {
          cnt++;
          entr += (sym_occur/total_size)*(log2(sym_occur/total_size));
        }
    }

  entr = -1*entr;
  return entr;
}

