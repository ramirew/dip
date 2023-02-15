#ifndef MOEMNT_H
#define MOEMNT_H

#include <iostream>
#include <vector>

//se define una clase llamada "moment". La clase tiene un constructor predeterminado y una función llamada "f5_idm" que toma una matriz 2D "P" 
//y un entero "Ng" como argumentos y devuelve un valor de punto flotante "double".

//La función "f5_idm" calcula un momento de segundo orden denominado "Inversión Diferencial de Momento"
using namespace std;

class moment;

class moment
{
public:
    moment();
    double f5_idm (double **P, int Ng) const;
};

#endif
