#include "libreriaGeometria.h"
#include <algorithm>
#include <cmath>
#include <numeric>
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



// Constructor
ImageAsymmetry::ImageAsymmetry() {}

// Método para encontrar la asimetría de una imagen
double ImageAsymmetry::find(const std::vector<Pixel>& pixels, int width, int height) {
    if (pixels.empty()) return 0;

    // Calcular la media de la intensidad de los pixels
    double mean = std::accumulate(pixels.begin(), pixels.end(), 0.0, [](double a, Pixel b) {
        return a + b.intensity;
    }) / pixels.size();

    // Calcular la suma de los pixels a la izquierda y a la derecha de la media
    double leftSum = 0, rightSum = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            if (pixels[index].intensity < mean) {
                leftSum += pixels[index].intensity;
            } else {
                rightSum += pixels[index].intensity;
            }
        }
    }

    // Devolver la asimetría como la diferencia entre las dos sumas
    return rightSum - leftSum;
}
