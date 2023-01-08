#include <iostream>
#include "..feature_ext_sel/first_order/firstorderclassifiers.h" /*arreglar ruta*/
#include "..feature_ext_sel/first_order/entropy.h" /*arreglar ruta*/
#include "..classification/dicom_read/DicomReader.h" /*arreglar ruta*/
#include "dcmtk/dcmimgle/dcmimage.h"

using namespace std;

int main()
{
  /* Imagen y archivo CSV se encuentran en la carpeta data */
  cout << "Clasificadores de Primer Orden" << endl;
  FirstOrderClassifiers f;
  Entropy e;

  DicomReader dicomObj("20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
  DicomImage DCM_image("20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");

  int depth = DCM_image.getDepth();
  int width = dicomObj.getWidth();
  int height = dicomObj.getHeight();
  cout<<"Filas: "<<height<<endl;
  cout<<"Columnas: "<<width<<endl;
  cout<<"Profundidad de la imagen: "<<depth<<endl;

  vector<vector<int>> arr = dicomObj.getIntImageMatrix(depth);
  int tam_histo = e.countlinesCSV("histograma.csv");
  vector<int> histograma = e.readCSV("histograma.csv");

  cout<<"------------------------"<<endl;

  cout<<"entropy: "<<e.entropy(histograma,width,height,tam_histo)<<endl;

  vector<double> mean1 = f.mean1(arr,0);
  cout<<"Media: "<<mean1[0]<<endl;

  vector<double> std = f.STD_VAR(arr,0);
  cout<< "La desviación estandar: "<<std[0]<<endl;

  vector<double> var = f.STD_VAR(arr,1);
  cout<< "La Varianza: "<<var[0]<<endl;

  double kur = f.Kurtosis(arr,1);
  cout<<"La kurtosis es: "<<kur<<endl;

  double skw = f.Skewness(arr,0);
  cout<<"Skewness: "<<skw<<endl;

  double max = f.MaxValue(arr);
  cout<<"Máximo valor: "<< max <<endl;

  double min = f.MinValue(arr);
  cout<<"Mínimo valor: "<< min <<endl;
  return 0;
}
