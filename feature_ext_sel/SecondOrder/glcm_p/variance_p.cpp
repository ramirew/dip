#include "variance_p.h"
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "xlsxwriter.h"
#include <omp.h>

using namespace cv;
using namespace std;

//DEFINICIONES DE PARAMETRICAS
#define PGM_MAXMAXVAL 255
#define EPSILON 0.000000001
#define RADIX 2.0
#define SIGN(x,y) ((y)<0 ? -fabs(x) : fabs(x))
#define SWAP(a,b) {y=(a);(a)=(b);(b)=y;}

variance_p::variance_p(){

}

//Initialize functions that have been used for measuring co-occurence matrixes for 0,45,90,135 degree angle
double** CoOcMat_Angle_0   (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_45  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_90  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_135 (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//INICIALIZAR FUNCIONES
double f1_asm (double **P, int Ng);

//RECURSOS DE LOS METODOS
double *allocate_vector (int nl, int nh);
double **allocate_matrix (int nrl, int nrh, int ncl, int nch);
void free_matrix(double **matrix,int nrh);

/**
Se declara una variable var para acumular el resultado del cálculo de la varianza de segundo orden.
Se crea un arreglo llamado Pxpy que tendrá una longitud de 2 * Ng + 1 elementos, donde Ng es el número de niveles de gris. Cada elemento del arreglo Pxpy será inicializado en cero.
Se recorre la matriz de co-ocurrencia P y se acumulan los valores de probabilidad para cada valor de sumatoria i+j en el arreglo Pxpy.
Se calcula la varianza de segundo orden sumando el cuadrado de la diferencia entre el índice de sumatoria y el valor medio de la sumatoria, 
ponderado por la probabilidad de que esa sumatoria se produzca, para cada posible valor de sumatoria. La suma se realiza desde 0 hasta 2 * Ng - 2.
Finalmente, se libera la memoria del arreglo Pxpy y se devuelve el resultado de la varianza de segundo orden.

*/

//SUM VARIANCE
double variance_p::f7_svar (double **P, int Ng, double S, int hilos) const {
    int i, j;
    double var = 0;
    double *Pxpy = allocate_vector(0, 2*Ng);
    //#pragma omp parallel num_threads(hilos)
    {
        #pragma omp for schedule(static)
        for (i = 0; i <= 2 * Ng; ++i)
            Pxpy[i] = 0;

        for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j)
              Pxpy[i + j] += P[i][j];

        for (i = 0; i <= (2 * Ng - 2); ++i)
            var += (i - S) * (i - S) * Pxpy[i];
    }
    free (Pxpy);
    return var;
}

//10 DIFERENCIA VARIANZA
double variance_p::f10_dvar (double **P, int Ng, int hilos) const {
    int i, j;
    double sum = 0, sum_sqr = 0, var = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);
    //#pragma omp parallel num_threads(hilos)
    {
        for (i = 0; i <= 2 * Ng; ++i)
            Pxpy[i] = 0;

        for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j)
                Pxpy[abs (i - j)] += P[i][j];

        for (i = 0; i < Ng; ++i) {
            sum += i * Pxpy[i] ;
            sum_sqr += i * i * Pxpy[i] ;
        }
    }
    var = sum_sqr - sum*sum ;
    free (Pxpy);
    return var;
}



