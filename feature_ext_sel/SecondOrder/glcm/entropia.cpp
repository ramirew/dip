#include "entropia.h"
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
/*
PGM_MAXMAXVAL: Define el valor máximo que se puede tener en un archivo de imagen en formato PGM.
EPSILON: Define una constante muy pequeña para evitar divisiones por cero.
RADIX: Define la base del logaritmo que se utiliza para calcular la entropía.
SIGN(x,y): Macro que devuelve el valor absoluto de x con el signo de y.
SWAP(a,b): Macro que intercambia los valores de a y b.

*/
#define PGM_MAXMAXVAL 255
#define EPSILON 0.000000001
#define RADIX 2.0
#define SIGN(x,y) ((y)<0 ? -fabs(x) : fabs(x))
#define SWAP(a,b) {y=(a);(a)=(b);(b)=y;}

entropia::entropia(){

}

//Initialize functions that have been used for measuring co-occurence matrixes for 0,45,90,135 degree angle
/*
CoOcMat_Angle_0: función que calcula la matriz de co-ocurrencia para ángulos de 0 grados.
CoOcMat_Angle_45: función que calcula la matriz de co-ocurrencia para ángulos de 45 grados.
CoOcMat_Angle_90: función que calcula la matriz de co-ocurrencia para ángulos de 90 grados.
CoOcMat_Angle_135: función que calcula la matriz de co-ocurrencia para ángulos de 135 grados.
*/
double** CoOcMat_Angle_0   (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_45  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_90  (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);
double** CoOcMat_Angle_135 (int distance, u_int16_t **grays, int rows, int cols, int* tone_LUT, int tone_count);

//INICIALIZAR FUNCIONES
/*
f1_asm: función que calcula el "angular second moment", una medida de uniformidad en la matriz de co-ocurrencia.
*/
double f1_asm (double **P, int Ng);

//RECURSOS DE LOS METODOS
/*
allocate_vector: Reserva memoria dinámica para un vector de tamaño
llocate_matrix: Reserva memoria dinámica para una matriz
ree_matrix: Libera la memoria asignada a una matriz previamente creada con allocate_matrix.
*/
double *allocate_vector (int nl, int nh);
double **allocate_matrix (int nrl, int nrh, int ncl, int nch);
void free_matrix(double **matrix,int nrh);

//SUMA ENTROPIA
/*
f8_sentropy: función que calcula la suma de entropía a partir de la matriz de co-ocurrencia.
*/
double entropia::f8_sentropy (double **P, int Ng) const {
    int i, j;
    double sentropy = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);
    for (i = 0; i <= 2 * Ng; ++i)
        Pxpy[i] = 0;
    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
          Pxpy[i + j + 2] += P[i][j];
    for (i = 2; i <= 2 * Ng; ++i)
        sentropy -= Pxpy[i] * log10 (Pxpy[i] + EPSILON)/log10(2.0) ;
    free (Pxpy);
    return sentropy;
}

//9 ENTROPIA
/*
f9_entropy: función que calcula la entropía a partir de la matriz de co-ocurrencia.
*/
double entropia::f9_entropy (double **P, int Ng) const {
    int i, j;
    double entropy = 0;
    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            entropy += P[i][j] * log10 (P[i][j] + EPSILON)/log10(2.0) ;
    return -entropy;
}


//11 DIFERENCIA ENTROPIA
/*
f11_dentropy: función que calcula la diferencia de entropía a partir de la matriz de co-ocurrencia.
*/
double entropia::f11_dentropy (double **P, int Ng) const {
    int i, j;
    double sum = 0;
    double *Pxpy = allocate_vector (0, 2*Ng);

    for (i = 0; i <= 2 * Ng; ++i)
        Pxpy[i] = 0;

    for (i = 0; i < Ng; ++i)
        for (j = 0; j < Ng; ++j)
            Pxpy[abs (i - j)] += P[i][j];

    for (i = 0; i < Ng; ++i)
        /*    sum += Pxpy[i] * log10 (Pxpy[i] + EPSILON); */
        sum += Pxpy[i] * log10 (Pxpy[i] + EPSILON)/log10(2.0) ;

    free (Pxpy);
    return -sum;
}


