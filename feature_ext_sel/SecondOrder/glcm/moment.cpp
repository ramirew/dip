#include "moment.h"
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

//define la macro "PGM_MAXMAXVAL" y le asigna el valor de 255
#define PGM_MAXMAXVAL 255

//define la macro "EPSILON" y le asigna el valor de 0.000000001
#define EPSILON 0.000000001

//define la macro "RADIX" y le asigna el valor de 2.0.
#define RADIX 2.0

//define la macro "SIGN(x,y)" que es una función de signo que toma dos argumentos "x" e "y" y devuelve el valor absoluto de "x" 
//si "y" es mayor o igual a cero y el valor absoluto de "x" multiplicado por -1 si "y" es menor que cero.
#define SIGN(x,y) ((y)<0 ? -fabs(x) : fabs(x))

//define la macro "SWAP(a,b)" que es una función de intercambio que toma dos argumentos "a" y "b" y los intercambia
#define SWAP(a,b) {y=(a);(a)=(b);(b)=y;}


moment::moment(){

}

//Initialize functions that have been used for measuring co-occurence matrixes for 0,45,90,135 degree angle

//calcula una matriz de coocurrencia para pares de píxeles separados por una distancia en ángulo de 0 grados.
double** CoOcMat_Angle_0   (int distance, u_int8_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//calcula una matriz de coocurrencia para pares de píxeles separados por una distancia en ángulo de 45 grados.
double** CoOcMat_Angle_45  (int distance, u_int8_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

// calcula una matriz de coocurrencia para pares de píxeles separados por una distancia en ángulo de 90 grados.
double** CoOcMat_Angle_90  (int distance, u_int8_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//calcula una matriz de coocurrencia para pares de píxeles separados por una distancia en ángulo de 135 grados.
double** CoOcMat_Angle_135 (int distance, u_int8_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//INICIALIZAR FUNCIONES
double f1_asm (double **P, int Ng);

//RECURSOS DE LOS METODOS
double *allocate_vector (int nl, int nh);
double **allocate_matrix (int nrl, int nrh, int ncl, int nch);
void free_matrix(double **matrix,int nrh);


//8 INVERSE DIFERENCE MOEMNT
//La función calcula el valor del Momento de Distancia Inversa (Inverse Difference Moment, IDM) para una matriz de nivel de gris P de tamaño Ng x Ng.
double moment::f5_idm (double **P, int Ng) const {
    int i, j;
    double idm = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            idm += P[i][j] / (1 + (i - j) * (i - j));

    return idm;
}



