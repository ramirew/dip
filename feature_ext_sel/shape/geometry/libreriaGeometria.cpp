#include "libreriaGeometria.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<bits/stdc++.h>


#define CANTIDAD_ALUMNOS 3
#define CANTIDAD_MATERIAS 3
#define MAXIMA_CALIFICACION 100
#define MINIMA_CALIFICACION 0
#define MAXIMA_LONGITUD_CADENA 100
#include <iostream>
#include <complex>
#include <cmath>
#include <iterator>

using namespace std;





unsigned int bitReverse(unsigned int x, int log2n) {
  int n = 0;
  int mask = 0x1;
  for (int i=0; i < log2n; i++) {
    n <<= 1;
    n |= (x & 1);
    x >>= 1;
  }
  return n;
}


void fft(Iter_T a, Iter_T b, int log2n,double PI)
{
  typedef typename iterator_traits<Iter_T>::value_type complex;
  const complex J(0, 1);
  int n = 1 << log2n;
  for (unsigned int i=0; i < n; ++i) {
    b[bitReverse(i, log2n)] = a[i];
  }
  for (int s = 1; s <= log2n; ++s) {
    int m = 1 << s;
    int m2 = m >> 1;
    complex w(1, 0);
    complex wm = exp(-J * (PI / m2));
    for (int j=0; j < m2; ++j) {
      for (int k=j; k < n; k += m) {
        complex t = w * b[k + m2];
        complex u = b[k];
        b[k] = u + t;
        b[k + m2] = u - t;
      }
      w *= wm;
    }
  }
}






int aleatorio_en_rango(int minimo, int maximo)
{
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void llenarMatriz(float matriz[CANTIDAD_ALUMNOS][CANTIDAD_MATERIAS + 1])
{
    int y, x;
    for (y = 0; y < CANTIDAD_ALUMNOS; y++)
    {
        float suma = 0;
        for (x = 0; x < CANTIDAD_MATERIAS; x++)
        {
            int calificacion = aleatorio_en_rango(MINIMA_CALIFICACION, MAXIMA_CALIFICACION);
            suma += (float)calificacion;
            matriz[y][x] = calificacion;
        }
        // Agregar promedio
        float promedio = suma / CANTIDAD_MATERIAS;
        matriz[y][CANTIDAD_MATERIAS] = promedio;
    }
}

void imprimirLinea()
{
    int x;
    printf("+----------");
    for (x = 0; x < CANTIDAD_MATERIAS + 1; x++)
    {
        printf("+--------");
    }
    printf("+\n");
}

void imprimir(float matriz[CANTIDAD_ALUMNOS][CANTIDAD_MATERIAS + 1], char alumnos[CANTIDAD_ALUMNOS][MAXIMA_LONGITUD_CADENA])
{
    int y, x;
    float promedioMayor = matriz[0][CANTIDAD_MATERIAS];
    float promedioMenor = matriz[0][CANTIDAD_MATERIAS];
    char alumnoPromedioMayor[MAXIMA_LONGITUD_CADENA];
    char alumnoPromedioMenor[MAXIMA_LONGITUD_CADENA];
    memcpy(alumnoPromedioMayor, alumnos[0], MAXIMA_LONGITUD_CADENA);
    memcpy(alumnoPromedioMenor, alumnos[0], MAXIMA_LONGITUD_CADENA);

    imprimirLinea();
    printf("|  Alumno  |");
    for (x = 0; x < CANTIDAD_MATERIAS; x++)
    {
        printf("Cal %d   |", x + 1);
    }
    printf("Promedio|\n");
    imprimirLinea();
    for (y = 0; y < CANTIDAD_ALUMNOS; y++)
    {
        printf("|%-10s|", alumnos[y]);
        float suma = 0;
        for (x = 0; x < CANTIDAD_MATERIAS; x++)
        {
            int calificacion = matriz[y][x];
            printf("%-7d |", calificacion);
        }
        float promedio = matriz[y][CANTIDAD_MATERIAS];
        if (promedio > promedioMayor)
        {
            promedioMayor = promedio;
            memcpy(alumnoPromedioMayor, alumnos[y], MAXIMA_LONGITUD_CADENA);
        }
        if (promedio < promedioMenor)
        {
            promedioMenor = promedio;
            memcpy(alumnoPromedioMenor, alumnos[y], MAXIMA_LONGITUD_CADENA);
        }
        printf("%0.2f   |\n", promedio);
        imprimirLinea();
    }
    printf("Promedio mayor: %s con %0.2f\n", alumnoPromedioMayor, promedioMayor);
    printf("Promedio menor: %s con %0.2f\n", alumnoPromedioMenor, promedioMenor);
}


 
// Function to calculate
// mean of data.
float mean(float arr[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + arr[i];       
    return sum / n;
}
 
// Function to calculate standard
// deviation of data.
float standardDeviation(float arr[],
                        int n)
{
    float sum = 0;
     
    // find standard deviation
    // deviation of data.
    for (int i = 0; i < n; i++)
        sum = (arr[i] - mean(arr, n)) *
              (arr[i] - mean(arr, n));
               
    return sqrt(sum / n);
}
 
// Function to calculate skewness.
float skewness(float arr[], int n)
{  
    // Find skewness using above formula
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum = (arr[i] - mean(arr, n)) *
              (arr[i] - mean(arr, n)) *
              (arr[i] - mean(arr, n));             
    return sum / (n * standardDeviation(arr, n) *
                 standardDeviation(arr, n) *
                 standardDeviation(arr, n) *
                 standardDeviation(arr, n));
}

