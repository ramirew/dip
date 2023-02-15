#ifndef MESURE_P_H
#define MESURE_P_H

#include <iostream>
#include <vector>

/*
//se define una clase mesure con tres miembros: un constructor predeterminado y dos funciones miembro, 
f12_icorr y f13_icorr, que toman como argumentos un puntero a una matriz 2D de tipo double y un entero Ng.
*/
using namespace std;

class mesure_p;

class mesure_p
{
public:
    mesure_p();
    double f12_icorr (double **P, int Ng, int hilos) const;
    double f13_icorr (double **P, int Ng, int hilos) const;
};

#endif
