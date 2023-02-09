#ifndef LIBRERIAGEOMETRIA_H_INCLUDED
#define LIBRERIAGEOMETRIA_H_INCLUDED

#pragma once

#include <vector>
#include <complex>
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


// Clase ImageCircularity para encontrar la circularidad de una imagen
class ImageCircularity {
public:
    // Constructor
    ImageCircularity();

    // Método para encontrar la circularidad de una imagen
    double find(const std::vector<Point>& contour);
};

//compactness or shape ---------
// Estructura para almacenar un punto en 2D

// Clase ImageCompactness para encontrar la compacidad o forma de una imagen
class ImageCompactness {
public:
    // Constructor
    ImageCompactness();

    // Método para encontrar la compacidad o forma de una imagen
    double find(const std::vector<Point>& contour);
};

//ellongation ------------------------
// Clase ImageElongation para encontrar el alargamiento de una imagen
class ImageElongation {
public:
    // Constructor
    ImageElongation();

    // Método para encontrar el alargamiento de una imagen
    double find(const std::vector<Point>& contour);
};

//form ------------------------
class Shape {
	public:
	double calculateshape();
};
//FOURIER FEATURES ----------------------
// Clase ImageFourierFeatures para encontrar las características de Fourier de una imagen
class ImageFourierFeatures {
public:
    // Constructor
    ImageFourierFeatures();

    // Método para encontrar las características de Fourier de una imagen
    std::vector<std::complex<double>> find(const std::vector<Point>& contour);
};


//MONETOS DE DISTANCIA NORMALIZADOS  ----------------------
// Clase ImageNormalizedDistanceMoments para encontrar los momentos de distancia normalizados de una imagen
class ImageNormalizedDistanceMoments {
public:
    // Constructor
    ImageNormalizedDistanceMoments();

    // Método para encontrar los momentos de distancia normalizados de una imagen
    std::vector<double> find(const std::vector<Point>& contour);
};
// radius -----------------------------------------------------
double calculateRadius(const std::vector<std::vector<int>>& image);


#endif // LIBRERIAGEOMETRIA_H_INCLUDED

//Orientacion relativa del gradiante ----------------------------

//13.-solidity
class Solidity {
 public:
  double calculateSolidity();
};