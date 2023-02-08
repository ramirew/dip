#include <iostream>
#include "classification/dicom_read/DicomReader.h" //arreglar referencia
#include "dcmtk/dcmimgle/dcmimage.h"
#include "feature_ext_sel/first_order/firstorderclassifiers.h" //arreglar referencia
#include "feature_ext_sel/first_order/entropy.h" //arreglar referencia
#include "feature_ext_sel/first_order/firstorderclassifiersparallel.h" //arreglar referencia
#include "feature_ext_sel/first_order/entropyparallel.h" //arreglar referencia
#include "metrics/performance/benchmark.h" //arreglar referencia
#include <vector>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif


using namespace std;

//clock_t t1, t2;
unsigned t1,t2;
double time_exec;
struct timespec ta,tb;

using namespace std;

int main()
{
  FirstOrderClassifiers f;
  FirstOrderClassifiersParallel fp;
  Entropy e;
  EntropyParallel ep;
  systemMetrics sm("secuencial");
  systemMetrics sm1("paralelo");
  vector<vector<int>> arr;

  const char *img;
  string hst;
  img = "../20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm"; //arreglar referencia
  hst = "../histograma.csv"; //arreglar referencia

  //Lectura de la imagen
  DicomReader dicomObj(img);
  DicomImage DCM_image(img);
  int depth = DCM_image.getDepth();
  int width = dicomObj.getWidth();
  int height = dicomObj.getHeight();
  cout<<"Filas: "<<height<<endl;
  cout<<"Columnas: "<<width<<endl;

  cout<<"++++++++++++++++++++++++++ENTROPIA+++++++++++++++++++++++++++++++++++++++++"<<endl;
  //Entropia secuencial
  sm.resetCounters();
  int tam_histo = e.countlinesCSV(hst);
  vector<int> histograma = e.readCSV(hst);
  cout<<"entropy: "<<e.entropy(histograma,width,height,tam_histo)<<endl;
  sm.calculate();
  sm.printMetrics();
  cout<<"RAM final Entropia (KB): "<<getRamUsage()<<endl;
  cout<<"------------------------------------------------------------------"<<endl;
  //Entropia paralela
  sm1.resetCounters();
  cout<<"RAM INICIO: "<<getRamUsage()<<endl;
  int tam_histo1 = ep.countlinesCSV("../histograma.csv");
  vector<int> histograma1 = ep.readCSV("../histograma.csv");
  cout<<"entropy parallel: "<<ep.entropy(histograma1,width,height,tam_histo1)<<endl;
  sm1.calculate();
  sm1.printMetrics();
  cout<<"RAM final Entropia Parallel (KB): "<<getRamUsage()<<endl;

  return 0;
}
