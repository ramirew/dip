#include "libreriaGeometria.h"

#include <cmath>
#include <iostream>

using namespace std;

float resolverEcuacion(float valor) {
  // Con la ecuación: x^3 + 4x^2 -10
  return pow(valor, 3) + 4 * pow(valor, 2) - 10;
}

float resolverDerivada(float valor) {
  // Con la ecuación: 2x^2 + 8x
  return pow((2 * valor), 2) + 8 * valor;
}