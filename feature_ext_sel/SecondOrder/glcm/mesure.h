#ifndef MESURE_H
#define MESURE_H

#include <iostream>
#include <vector>

//se define una clase mesure con tres miembros: un constructor predeterminado y dos funciones miembro, 
//f12_icorr y f13_icorr, que toman como argumentos un puntero a una matriz 2D de tipo double y un entero Ng.

using namespace std;

class mesure;

class mesure
{
public:
    mesure();
    double f12_icorr (double **P, int Ng) const;
    double f13_icorr (double **P, int Ng) const;
};

#endif
