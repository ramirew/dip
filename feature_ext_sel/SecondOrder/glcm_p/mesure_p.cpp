#include "mesure_p.h"
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
//define la macro "PGM_MAXMAXVAL" y le asigna el valor de 255
#define PGM_MAXMAXVAL 255

//define la macro "EPSILON" y le asigna el valor de 0.000000001
#define EPSILON 0.000000001

//define la macro "RADIX" y le asigna el valor de 2.0.
#define RADIX 2.0

//define la macro "SIGN(x,y)" que es una función de signo que toma dos argumentos "x" e "y" y devuelve el valor absoluto de "x" si "y" es mayor o igual a cero y el valor absoluto de "x" multiplicado por -1 si "y" es menor que cero.

#define SIGN(x,y) ((y)<0 ? -fabs(x) : fabs(x))

//define la macro "SWAP(a,b)" que es una función de intercambio que toma dos argumentos "a" y "b" y los intercambia

#define SWAP(a,b) {y=(a);(a)=(b);(b)=y;}


mesure_p::mesure_p(){

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


//6 INFORMATION MESURE CORRELATION 1 Y 2
/*
implementación de la función f12_icorr de una clase llamada mesure, la cual calcula el índice de correlación de información entre dos variables en una 
matriz de coocurrencia.

calcula las sumas de las filas y columnas de la matriz de coocurrencia P, lo cual será utilizado posteriormente para calcular el índice de correlación 
de información.
*/
double mesure_p::f12_icorr (double **P, int Ng, int hilos) const {
    int i, j;
    double *px, *py;
    double hx = 0, hy = 0, hxy = 0, hxy1 = 0, hxy2 = 0;
    px = allocate_vector (0, Ng);
    py = allocate_vector (0, Ng);
    //#pragma omp parallel num_threads(hilos)
    {
        for (i = 0; i < Ng; ++i) {
            for (j = 0; j < Ng; ++j) {
                px[i] += P[i][j];
                py[j] += P[i][j];
            }
        }
        for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j) {
                hxy1 -= P[i][j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
                hxy2 -= px[i] * py[j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
                hxy -= P[i][j] * log10 (P[i][j] + EPSILON)/log10(2.0);
            }
        for (i = 0; i < Ng; ++i) {
            hx -= px[i] * log10 (px[i] + EPSILON)/log10(2.0);
            hy -= py[i] * log10 (py[i] + EPSILON)/log10(2.0);
        }
    }
    free(px);
    free(py);
        if ((hx > hy ? hx : hy)==0) return(1);
        else
    return ((hxy - hxy1) / (hx > hy ? hx : hy));
}

/*
define una función llamada f13_icorr en una clase llamada mesure. La función toma una matriz 2D P y un entero Ng como entrada, y devuelve un valor de tipo double.
a función primero declara variables locales i, j, px, py, hx, hy, hxy, hxy1, hxy2 de tipo int y double.
Luego, la función asigna memoria dinámicamente para dos vectores px y py utilizando la función allocate_vector. La función luego inicializa px y py a cero.
*/

double mesure_p::f13_icorr (double **P, int Ng, int hilos) const {
    int i, j;
    double *px, *py;
    double hx = 0, hy = 0, hxy = 0, hxy1 = 0, hxy2 = 0;
    px = allocate_vector (0, Ng);
    py = allocate_vector (0, Ng);
    //#pragma omp parallel num_threads(hilos)
    {
        for (i = 0; i < Ng; ++i) {
            for (j = 0; j < Ng; ++j) {
              px[i] += P[i][j];
              py[j] += P[i][j];
            }
        }
        for (i = 0; i < Ng; ++i)
            for (j = 0; j < Ng; ++j) {
                hxy1 -= P[i][j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
                hxy2 -= px[i] * py[j] * log10 (px[i] * py[j] + EPSILON)/log10(2.0);
                hxy -= P[i][j] * log10 (P[i][j] + EPSILON)/log10(2.0);
            }
        for (i = 0; i < Ng; ++i) {
            hx -= px[i] * log10 (px[i] + EPSILON)/log10(2.0);
            hy -= py[i] * log10 (py[i] + EPSILON)/log10(2.0);
        }
     }
    free(px);
    free(py);
    return (sqrt (fabs (1 - exp (-2.0 * (hxy2 - hxy)))));
}

