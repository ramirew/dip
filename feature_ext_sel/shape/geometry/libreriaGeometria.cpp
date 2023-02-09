#include "libreriaGeometria.h"
#include <iostream>
#include <cmath>

using namespace std;

double media(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double desviacion_estandar(double arr[], int n) {
    double mean = media(arr, n);
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += pow


