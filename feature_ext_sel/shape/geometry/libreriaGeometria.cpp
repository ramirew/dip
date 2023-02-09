#include "libreriaGeometria.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para almacenar un punto en 2D
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Función para comparar dos puntos por su ángulo con respecto a un punto base
bool compare(Point a, Point b, Point base) {
    // Si los puntos están en la misma línea, devuelve el más lejano
    int dx1 = a.x - base.x, dy1 = a.y - base.y;
    int dx2 = b.x - base.x, dy2 = b.y - base.y;
    if (dx1 * dy2 == dx2 * dy1) {
        return (dx1 * dx1 + dy1 * dy1) < (dx2 * dx2 + dy2 * dy2);
    }

    // Devuelve el punto con un ángulo más bajo con respecto a la horizontal
    int angle = (dx1 * dx2 + dy1 * dy2) / (sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2)));
    int k = dy1 * dx2 - dx1 * dy2;
    return k > 0 || (k == 0 && angle < 0);
}

// Función para encontrar el borde convexo de un conjunto de puntos
vector<Point> convexHull(vector<Point>& points) {
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