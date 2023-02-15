#include "contraste_p.h"
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

contraste_p::contraste_p(){

}

//Initialize functions that have been used for measuring co-occurence matrixes for 0,45,90,135 degree angle
/*
CoOcMat_Angle_0: Calcula la matriz de coocurrencia para un ángulo de 0 grados.
CoOcMat_Angle_45: Calcula la matriz de coocurrencia para un ángulo de 45 grados.
CoOcMat_Angle_90: Calcula la matriz de coocurrencia para un ángulo de 90 grados.
CoOcMat_Angle_135: Calcula la matriz de coocurrencia para un ángulo de 135 grados.
*/
double** CoOcMat_Angle_0   (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_45  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_90  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_135 (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//INICIALIZAR FUNCIONES
/*
f1_asm: Calcula el momento angular de segundo orden de una matriz de coocurrencia.
*/
double f1_asm (double **P, int Ng);

//RECURSOS DE LOS METODOS
/*
allocate_vector: Asigna dinámicamente un vector de memoria con un rango de índices especificado.
allocate_matrix: Asigna dinámicamente una matriz de memoria con un rango de índices especificado.
free_matrix: Libera la memoria de una matriz previamente asignada con allocate_matrix.
*/
double *allocate_vector (int nl, int nh);
double **allocate_matrix (int nrl, int nrh, int ncl, int nch);
void free_matrix(double **matrix,int nrh);



//7 CONTRASTE
/*
f2_contrast: Calcula el contraste de una matriz de coocurrencia utilizando la fórmula sumatoria de la diferencia de intensidades elevada al cuadrado.
*/
double contraste_p::f2_contrast (double **P, int Ng, int hilos) const {
    int i, j, n;
    double sum = 0, bigsum = 0;
    //#pragma omp parallel num_threads(hilos)
        {
            for (n = 0; n < Ng; ++n) {
                for (i = 0; i < Ng; ++i)
                    for (j = 0; j < Ng; ++j) {
                        if ((i - j) == n || (j - i) == n)
                            sum += P[i][j];
                        }
                bigsum += n * n * sum;
                sum = 0;
            }
        }
    return bigsum;
}

