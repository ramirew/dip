#include "firstorderclassifiers.h"
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

FirstOrderClassifiers::FirstOrderClassifiers()
{

}

void FirstOrderClassifiers::muestra_vector(const vector<int>& v)
{
  for (auto x : v)
    cout << x << " ";
  cout << endl;
}

/**
 * Método para calcular la media de una imagen global, por fila o por columna
 * @param arr matriz obtenida de la lectura de la imagen
 * @param type bandera
 * 0: media de la matriz completa
 * 1: media de la matriz por fila
 * 2: media de la matriz por columna
 * @return mean value or mean vector
 */
vector<double> FirstOrderClassifiers::mean1(vector<vector<int>>arr,int type=0)
{
  vector<double> mean;
  double suma;
  if (type == 0){
    suma = 0;
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
      for (unsigned int j = 0; j < arr[i].size(); ++j)
      {
//        suma = suma + arr[i][j];
        suma = suma + abs(arr[i][j]);
      }
    }
    mean.push_back(suma/(arr.size()*arr[0].size()));
  }
  else{
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
      suma = 0;
      for (unsigned int j = 0; j < arr[i].size(); ++j)
      {
          if (type == 1){
            suma = suma + arr[i][j];
          }
          else if (type == 2){
            suma = suma + arr[j][i];
          }
      }
     if( type == 1){
       mean.push_back(suma/arr[i].size());
     }
     else if (type == 2){
       mean.push_back(suma/arr.size());
     }
    }
   }
  return mean;
}

/**
 * Método para calcular la desviación estandar o la varianza de la imagen
 * @param arr matriz obtenida de la lectura de la imagen
 * @param row
 * @param column
 * @param type bandera
 * 0: desviación estandar
 * 1: varianza
 * @return variance value or std value
 */
vector<double> FirstOrderClassifiers::STD_VAR(vector<vector<int>>arr,int type)
{
  vector<double> std_var;
  vector<double> mean = this->mean1(arr);
  float suma = 0;

  for(unsigned int i = 0; i < arr.size(); i++)
    {
      for(unsigned int j = 0; j < arr[i].size(); j++)
        {
          suma += pow((arr[i][j]-mean[0]),2);
        }
    }

  float var = suma/(arr.size()*arr[0].size());
  if ( type == 0)
    {
      std_var.push_back(sqrt(var));
    }
  else if ( type == 1)
    {
      std_var.push_back(var);
    }

  return std_var;
}

/**
 * Método para calcular la Kurtosis de una imagen
 * @param arr matriz obtenida de la lectura de la imagen
 * @param flag bandera
 * 0: kurtosis systematic bias
 * 1: kustosis biased
 * @return kurtosis value
 */
double FirstOrderClassifiers::Kurtosis(vector<vector<int>>arr,int flag)
{
  vector<double> mean,var;
  mean = this->mean1(arr);
  var = this -> STD_VAR(arr,1);
  double kurtosis,k1,suma,n;
  kurtosis = 0;
  n = arr.size()*arr[0].size();
  if (flag == 1 )
    {
      suma = 0;
      for(unsigned int i = 0; i < arr.size(); i++)
        {
          for(unsigned int j = 0; j < arr[i].size(); j++)
            {
              suma = suma + pow((arr[i][j]-mean[0]),4);
            }
        }
      kurtosis = (suma/n)/pow(var[0],2);
    }

  else if ( flag == 0)
    {
      suma = 0;
      for(unsigned int i = 0; i < arr.size(); i++)
        {
          for(unsigned int j = 0; j < arr[i].size(); j++)
            {
              suma = suma + pow((arr[i][j]-mean[0]),4);
            }
        }
      k1 = (suma/n)/pow(var[0],2);
      kurtosis = (n-1)/((n-2)*(n-3)) * ((n+1)*k1 -3*(n-1)) + 3;
    }
  return kurtosis;
}

/**
 * Método para calcular la skewness o disperción de la imagen
 * @param arr matriz obtenida de la lectura de la imagen
 * @param flag
 * 0: kurtosis systematic bias
 * 1: kustosis biased
 * @return Skewness value
 */
double FirstOrderClassifiers::Skewness(vector<vector<int>>arr,int flag)
{
  vector<double> mean,std;
  mean = this->mean1(arr);
  std = this -> STD_VAR(arr,0);
  double skewness,sk1,suma,n;
  skewness = 0;
  n = arr.size()*arr[0].size();
  if (flag == 1 )
    {
      suma = 0;
      for(unsigned int i = 0; i < arr.size(); i++)
        {
          for(unsigned int j = 0; j < arr[i].size(); j++)
            {
              suma = suma + pow((arr[i][j]-mean[0]),3);
            }
        }
      skewness = (suma/n)/pow(std[0],3);
    }

  else if ( flag == 0)
    {
      suma = 0;
      for(unsigned int i = 0; i < arr.size(); i++)
        {
          for(unsigned int j = 0; j < arr[i].size(); j++)
            {
              suma = suma + pow((arr[i][j]-mean[0]),3);
            }
        }
      sk1 = (suma/n)/pow(std[0],3);
      skewness = (sqrt(n*(n-1))/(n-2))*sk1;
    }
  return skewness;
}

/**
 * Metodo para obtener el valor del mayor pixel de la imagen
 * @param arr matriz obtenida de la lectura de la imagen
 * @return max value
 */
double FirstOrderClassifiers::MaxValue(vector<vector<int>>arr){
  double value = arr[0][0];
  for (unsigned int i = 0;i < arr.size(); i++){
      for (unsigned int j = 0;j < arr[i].size(); j++){
          if ( arr[i][j] > value ){
              value = arr[i][j];
            }
        }
    }
  return value;
}

/**
 * Método para obtener el valor del menor pixel de la imagen
 * @param arr matriz obtenida de la lectura de la imagen
 * @return min value
 */
double FirstOrderClassifiers::MinValue(vector<vector<int>>arr){
  double value = arr[0][0];
  for (unsigned int i = 0;i < arr.size(); i++){
      for (unsigned int j = 0;j < arr[i].size(); j++){
          if ( arr[i][j] < value ){
              value = arr[i][j];
            }
        }
    }
  return value;
}
