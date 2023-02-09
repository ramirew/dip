#include "libreriaGeometria.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <algorithm>

//CONVEX --------------------
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


//ASYMETRY ----------------
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

//CIRCULARY ---------
// Constructor
ImageCircularity::ImageCircularity() {}

// Método para encontrar la circularidad de una imagen
double ImageCircularity::find(const std::vector<Point>& contour) {
    if (contour.empty()) return 0;

    // Calcular el centro de masa del contorno
    Point center;
    center.x = std::accumulate(contour.begin(), contour.end(), 0, [](int a, Point b) {
        return a + b.x;
    }) / contour.size();
    center.y = std::accumulate(contour.begin(), contour.end(), 0, [](int a, Point b) {
        return a + b.y;
    }) / contour.size();

    // Calcular la distancia promedio del centro de masa al contorno
    double avgDist = std::accumulate(contour.begin(), contour.end(), 0.0, [center](double a, Point b) {
        return a + sqrt((b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y));
    }) / contour.size();

    // Calcular el area del contorno
    double area = 0;
    for (int i = 0; i < contour.size() - 1; i++) {
        area += contour[i].x * contour[i + 1].y - contour[i].y * contour[i + 1].x;
    }
    area = fabs(area) / 2.0;

    // Calcular el area de la circunferencia con radio avgDist
    double circleArea = M_PI * avgDist * avgDist;

    // Devolver la circularidad como la relación entre el area del contorno y el area de la circunferencia
    return area / circleArea;
}
//compactness or shape ---------
// Constructor
ImageCompactness::ImageCompactness() {}

// Método para encontrar la compacidad o forma de una imagen
double ImageCompactness::find(const std::vector<Point>& contour) {
    if (contour.empty()) return 0;

    // Calcular los puntos de los extremos del rectángulo mínimo que envuelve el contorno
    int minX = contour[0].x, minY = contour[0].y;
    int maxX = contour[0].x, maxY = contour[0].y;
    for (const Point& p : contour) {
        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
    }

    // Calcular el área del contorno
    double area = 0;
    for (int i = 0; i < contour.size() - 1; i++) {
        area += contour[i].x * contour[i + 1].y - contour[i].y * contour[i + 1].x;
    }
    area = fabs(area) / 2.0;

    // Calcular el área del rectángulo mínimo que envuelve el contorno
    double rectArea = (maxX - minX) * (maxY - minY);

    // Devolver la compacidad o forma como la relación entre el área del contorno y el área del rectángulo mínimo
    return area / rectArea;
}