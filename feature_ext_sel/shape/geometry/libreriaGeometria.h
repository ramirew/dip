#ifndef LIBRERIAGEOMETRIA_H_INCLUDED
#define LIBRERIAGEOMETRIA_H_INCLUDED

#pragma once

#include <vector>

//CONVEX ------------------
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

//ASYMETRY ------------
struct Pixel {
    unsigned char intensity;
};

// Clase ImageAsymmetry para encontrar la asimetría de una imagen
class ImageAsymmetry {
public:
    // Constructor
    ImageAsymmetry();

    // Método para encontrar la asimetría de una imagen
    double find(const std::vector<Pixel>& pixels, int width, int height);
};

//CIRCULARY ---------
// Estructura para almacenar un punto en 2D
struct PointC {
    int x, y;
};

// Clase ImageCircularity para encontrar la circularidad de una imagen
class ImageCircularity {
public:
    // Constructor
    ImageCircularity();

    // Método para encontrar la circularidad de una imagen
    double find(const std::vector<PointC>& contour);
};


#endif // LIBRERIAGEOMETRIA_H_INCLUDED

