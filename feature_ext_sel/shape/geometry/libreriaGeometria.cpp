#include "libreriaGeometria.h"
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

// Constructor
ConvexHull::ConvexHull() {}

// Método para encontrar el borde convexo de un conjunto de puntos
std::vector<Point> ConvexHull::find(const std::vector<Point>& points) {
    if (points.size() <= 1) return points;

    // Encontrar el punto más bajo y hacerlo el punto base
    int minY = points[0].y, minIndex = 0;
    for (int i = 1; i < points.size(); i++) {
        int y = points[i].y;
        if ((y < minY) || (y == minY && points[i].x < points[minIndex].x)) {
            minY = y;
            minIndex = i;
        }
    }
    std::vector<Point> sortedPoints(points);
    std::swap(sortedPoints[0], sortedPoints[minIndex]);
    Point base = sortedPoints[0];

    // Ordenar los puntos por su ángulo con respecto a la base
    std::sort(sortedPoints.begin() + 1, sortedPoints.end(), [base](Point a, Point b) {
        return compare(a, b, base);
    });
}


double asimetrica(int filas, int columnas, double matriz[][columnas]){

for(int i=0; i<filas; i++){
for(int j=0; j<columnas; j++){
suma += matriz[i][j];
}
}
media = suma/(filascolumnas);
for(int i=0; i<filas; i++){
for(int j=0; j<columnas; j++){
varianza += pow(matriz[i][j]-media,2);
}
}
varianza = varianza/(filascolumnas);
desviacion = sqrt(varianza);
for(int i=0; i<filas; i++){
for(int j=0; j<columnas; j++){
asimetria += pow(matriz[i][j]-media,3);
}
}