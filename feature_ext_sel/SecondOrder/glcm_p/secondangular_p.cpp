#include "secondangular_p.h"
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


secondangular_p::secondangular_p(){

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



//SUM VARIANCE
/*
se implementa la función f1_asm que calcula la suma de los cuadrados de todos los elementos de la matriz de co-ocurrencia P. 
Este valor se utiliza para calcular otras características texturales, como la varianza, la entropía y la energía angular. 
La variable Ng es la dimensión de la matriz de co-ocurrencia y se utiliza para controlar el número de iteraciones en el bucle for anidado.
*/
double secondangular_p::f1_asm (double **P, int Ng, int hilos) const{
    int i, j;
    double sum = 0;
    //#pragma omp parallel num_threads(hilos)
    {
        for (i = 0; i < Ng; ++i){
            for (j = 0; j < Ng; ++j){
                sum += P[i][j] * P[i][j];
            }
        }
    }
    return sum;
}

