#include "averege.h"
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "xlsxwriter.h"


using namespace cv;
using namespace std;

//DEFINICIONES DE PARAMETRICAS
#define PGM_MAXMAXVAL 255
#define EPSILON 0.000000001
#define RADIX 2.0
#define SIGN(x,y) ((y)<0 ? -fabs(x) : fabs(x))
#define SWAP(a,b) {y=(a);(a)=(b);(b)=y;}

averege::averege(){

}

//Initialize functions that have been used for measuring co-occurence matrixes for 0,45,90,135 degree angle
/*CoOcMat_Angle_0: calcula la matriz de co-ocurrencia para un ángulo de 0 grados.
CoOcMat_Angle_45: calcula la matriz de co-ocurrencia para un ángulo de 45 grados.
CoOcMat_Angle_90: calcula la matriz de co-ocurrencia para un ángulo de 90 grados.
CoOcMat_Angle_135: calcula la matriz de co-ocurrencia para un ángulo de 135 grados.
*/
double** CoOcMat_Angle_0   (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_45  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_90  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_135 (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//INICIALIZAR FUNCIONES
//f1_asm: calcula el momento angular de la energía.
double f1_asm (double **P, int Ng);

//RECURSOS DE LOS METODOS
/**funciones de utilidad para la asignación de memoria:
    allocate_vector: asigna memoria para un vector.
    allocate_matrix: asigna memoria para una matriz.
    free_matrix: libera memoria asignada para una matriz.
*/
double *allocate_vector (int nl, int nh);
double **allocate_matrix (int nrl, int nrh, int ncl, int nch);
void free_matrix(double **matrix,int nrh);



//4 SUM AVEREGE
/**
El método f6_savg recibe una matriz de co-ocurrencia P, el número de niveles de gris Ng y el número de hilos hilos. Este método calcula una medida estadística llamada promedio de la suma (savg) utilizando la matriz de co-ocurrencia.
*/
double averege::f6_savg (double **P, int Ng) const {
    int i, j;
    double savg = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);

    for (i = 0; i <= 2 * Ng; ++i)
        Pxpy[i] = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
          Pxpy[i + j] += P[i][j];

    for (i = 0; i <= (2 * Ng - 2); ++i)
        savg += i * Pxpy[i];

    free (Pxpy);
    return savg;
}

