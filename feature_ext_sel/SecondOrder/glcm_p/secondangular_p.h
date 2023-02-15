#ifndef SECONDANGULAR_P_H
#define SECONDANGULAR_P_H

#include <iostream>
#include <vector>

/*
//se define una clase llamada "secondangular" que tiene un constructor público y una función pública llamada "f1_asm" que toma una matriz de doble puntero "P" 
y un entero "Ng" como argumentos y devuelve un valor de tipo double.
*/

using namespace std;

class secondangular_p;

class secondangular_p
{
public:
    secondangular_p();
    double f1_asm (double **P, int Ng, int hilos) const;
};

#endif
