#ifndef LIBRERIAGEOMETRIA_H_INCLUDED
#define LIBRERIAGEOMETRIA_H_INCLUDED

#pragma once

#include <vector>
#include <numeric>

// Estructura para almacenar un punto en 2D
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// Clase ConvexHull para encontrar el borde convexo de un conjunto de puntos
class ConvexHull {
public:
    // Constructor
    ConvexHull();

    // Método para encontrar el borde convexo de un conjunto de puntos
    std::vector<Point> find(const std::vector<Point>& points);

private:
    // Función para comparar dos puntos por su ángulo con respecto a un punto base
    static bool compare(Point a, Point b, Point base);
};

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


#endif // LIBRERIAGEOMETRIA_H_INCLUDED

