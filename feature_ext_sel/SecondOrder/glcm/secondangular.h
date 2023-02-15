#ifndef SECONDANGULAR_H
#define SECONDANGULAR_H

#include <iostream>
#include <vector>

//se define una clase llamada "secondangular" que tiene un constructor público y una función pública llamada "f1_asm" que toma una matriz 
//de doble puntero "P" y un entero "Ng" como argumentos y devuelve un valor de tipo double.
using namespace std;

class secondangular;

class secondangular
{
public:
    secondangular();
    double f1_asm (double **P, int Ng) const;
};

#endif
