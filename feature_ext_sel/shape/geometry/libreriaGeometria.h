#ifndef LIBRERIAGEOMETRIA_H_INCLUDED
#define LIBRERIAGEOMETRIA_H_INCLUDED

int aleatorio_en_rango(int minimo, int maximo);
void llenarMatriz(float matriz);
void imprimirLinea();
void imprimir(float matriz, char alumnos);
void imprimir(float matriz,char alumnos);
float mean(float arr[], int n);
float standardDeviation(float arr[],int n);
float skewness(float arr[], int n);
unsigned int bitReverse(unsigned int x, int log2n);
void fft(Iter_T a, Iter_T b, int log2n,double PI);
#include  "libreriaGeometria.cpp"

#endif // LIBRERIAGEOMETRIA_H_INCLUDED

