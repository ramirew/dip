#include "libreriaGeometria.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <omp.h>

//1.-CONVEX --------------------
// Constructor 
ConvexHull::ConvexHull() {}

// Método para encontrar el borde convexo de un conjunto de puntos
std::vector<Point> ConvexHull::find(const std::vector<Point>& points) {
    if (points.size() <= 1) return points;
    // Encontrar el punto más bajo y hacerlo el punto base
    int minY = points[0].y, minIndex = 0;
	#pragma omp parallel for
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


//2.-ASYMETRY ----------------
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
	omp_set_num_threads(NUM_THREADS);
	
	#pragma omp parallel for
    for (int y = 0; y < height; y++) {
		#pragma omp parallel for
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

//3.-CIRCULARY ---------
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
	#pragma omp parallel for
    for (int i = 0; i < contour.size() - 1; i++) {
        area += contour[i].x * contour[i + 1].y - contour[i].y * contour[i + 1].x;
    }
    area = fabs(area) / 2.0;

    // Calcular el area de la circunferencia con radio avgDist
    double circleArea = M_PI * avgDist * avgDist;

    // Devolver la circularidad como la relación entre el area del contorno y el area de la circunferencia
    return area / circleArea;
}
//4.-ompactness or shape ---------
// Constructor
ImageCompactness::ImageCompactness() {}

// Método para encontrar la compacidad o forma de una imagen
double ImageCompactness::find(const std::vector<Point>& contour) {
    if (contour.empty()) return 0;

    // Calcular los puntos de los extremos del rectángulo mínimo que envuelve el contorno
    int minX = contour[0].x, minY = contour[0].y;
    int maxX = contour[0].x, maxY = contour[0].y;
	#pragma omp parallel for
    for (const Point& p : contour) {
        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
    }

    // Calcular el área del contorno
    double area = 0;
	#pragma omp parallel for
    for (int i = 0; i < contour.size() - 1; i++) {
        area += contour[i].x * contour[i + 1].y - contour[i].y * contour[i + 1].x;
    }
    area = fabs(area) / 2.0;

    // Calcular el área del rectángulo mínimo que envuelve el contorno
    double rectArea = (maxX - minX) * (maxY - minY);

    // Devolver la compacidad o forma como la relación entre el área del contorno y el área del rectángulo mínimo
    return area / rectArea;
}

//5.-ellongation ------------------------
// Constructor
ImageElongation::ImageElongation() {}

// Método para encontrar el alargamiento de una imagen
double ImageElongation::find(const std::vector<Point>& contour) {
    if (contour.empty()) return 0;

    // Calcular el centro de masa de la imagen
    double xMean = 0, yMean = 0;
	#pragma omp parallel for
    for (const Point& p : contour) {
        xMean += p.x;
        yMean += p.y;
    }
    xMean /= contour.size();
    yMean /= contour.size();

    // Calcular el diámetro máximo de la imagen
    double maxDiameter = 0;
	#pragma omp parallel for
    for (const Point& p : contour) {
        maxDiameter = std::max(maxDiameter, std::sqrt(std::pow(p.x - xMean, 2) + std::pow(p.y - yMean, 2)));
    }

    // Calcular el diámetro mínimo de la imagen
    double minDiameter = std::numeric_limits<double>::max();
	#pragma omp parallel for
    for (const Point& p1 : contour) {
		#pragma omp parallel for
        for (const Point& p2 : contour) {
            minDiameter = std::min(minDiameter, std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2)));
        }
    }

    // Devolver el alargamiento como la relación entre el diámetro máximo y el diámetro mínimo
    return maxDiameter / minDiameter;
}
//6.-form ------------------------
double calculateshape(double area, double perimeter) {
  return (4 * M_PI * area) / (perimeter * perimeter);
}
//7.-FOURIER FEATURES ----------------------
// Constructor
ImageFourierFeatures::ImageFourierFeatures() {}

// Método para encontrar las características de Fourier de una imagen
std::vector<std::complex<double>> ImageFourierFeatures::find(const std::vector<Point>& contour) {
    if (contour.empty()) return {};

    // Calcular la transformada de Fourier de la imagen
    const int N = contour.size();
    std::vector<std::complex<double>> X(N);
	#pragma omp parallel for
    for (int k = 0; k < N; k++) {
        X[k] = {0, 0};
		#pragma omp parallel for
        for (int n = 0; n < N; n++) {
            double theta = 2 * M_PI * k * n / N;
            X[k].real(X[k].real() + contour[n].x * std::cos(theta) - contour[n].y * std::sin(theta));
            X[k].imag(X[k].imag() + contour[n].x * std::sin(theta) + contour[n].y * std::cos(theta));
        }
    }

    return X;
}
//8.-MONETOS DE DISTANCIA NORMALIZADOS  ----------------------
// Constructor
ImageNormalizedDistanceMoments::ImageNormalizedDistanceMoments() {}

// Método para encontrar los momentos de distancia normalizados de una imagen
std::vector<double> ImageNormalizedDistanceMoments::find(const std::vector<Point>& contour) {
    if (contour.empty()) return {};

    // Calcular los momentos de distancia normalizados de la imagen
    const int N = contour.size();
    const double cx = 0.5 * (contour[0].x + contour[N - 1].x);
    const double cy = 0.5 * (contour[0].y + contour[N - 1].y);
    double m00 = 0;
    double m10 = 0;
    double m01 = 0;
	#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double dx = contour[i].x - cx;
        double dy = contour[i].y - cy;
        double d = std::sqrt(dx * dx + dy * dy);
        m00 += d;
        m10 += d * dx;
        m01 += d * dy;
    }
    m00 /= N;
    m10 /= N;
    m01 /= N;

    return {m00, m10, m01};
}
//9.la longitud radial normalizada------------------------
NormalizedRadialLength::NormalizedRadialLength(int height, int width) : height(height), width(width) {}

std::vector<double> NormalizedRadialLength::calculate(const std::vector<std::vector<double>> &image) {
    std::vector<double> result(height * width, 0);
    int centerX = width / 2;
    int centerY = height / 2;
    double maxRadius = std::sqrt(centerX * centerX + centerY * centerY);
#	pragma omp parallel for
    for (int i = 0; i < height; i++) {
		#pragma omp parallel for
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            double dx = j - centerX;
            double dy = i - centerY;
            double radialLength = std::sqrt(dx * dx + dy * dy) / maxRadius;
            result[index] = radialLength;
        }
    }

    return result;
}
//10.-radius -------------------------------
double calculateRadius(const std::vector<std::vector<int>>& image) {
    int row_num = image.size();
    int col_num = image[0].size();

    int center_x = row_num / 2;
    int center_y = col_num / 2;

    double sum = 0;
	#pragma omp parallel for
    for (int i = 0; i < row_num; i++) {
		#pragma omp parallel for
        for (int j = 0; j < col_num; j++) {
            if (image[i][j] > 0) {
                sum += std::sqrt((i - center_x) * (i - center_x) + (j - center_y) * (j - center_y));
            }
        }
    }

    int count = 0;
	#pragma omp parallel for
    for (int i = 0; i < row_num; i++) {
		#pragma omp parallel for
        for (int j = 0; j < col_num; j++) {
            if (image[i][j] > 0) {
                count++;
            }
        }
    }

    return sum / count;
}

//11.-Orientacion relativa del gradiante ----------------------------
double gradientX(const std::vector<std::vector<double>> &image, int x, int y) {
  // Calcular gradiente en x usando una máscara de Sobel
  double gx = image[x-1][y-1] + 2 * image[x][y-1] + image[x+1][y-1] -
              image[x-1][y+1] - 2 * image[x][y+1] - image[x+1][y+1];
  return gx;
}

double gradientY(const std::vector<std::vector<double>> &image, int x, int y) {
  // Calcular gradiente en y usando una máscara de Sobel
  double gy = image[x-1][y-1] + 2 * image[x-1][y] + image[x-1][y+1] -
              image[x+1][y-1] - 2 * image[x+1][y] - image[x+1][y+1];
  return gy;
}

double orientationRelativeGradient(const std::vector<std::vector<double>> &image, int x, int y) {
	
  double gx = gradientX(image, x, y);
  double gy = gradientY(image, x, y);

  // Calcular ángulo entre gradientes
  double angle = atan2(gy, gx) * 180 / PI;

  // Normalizar ángulo a un rango de 0 a 360 grados
  if (angle < 0) {
    angle += 360;
  }

  return angle;
}

//12.-REDONDEZ------------------------------------------
//Función para calcular el perímetro de una imagen
int calcPerimeter(const int *image, int width, int height) {
    int perimeter = 0;
	#pragma omp parallel for
    for (int i = 0; i < height; i++) {
		#pragma omp parallel for
        for (int j = 0; j < width; j++) {
            if (image[i * width + j] > 0) {
                // Si el píxel es blanco, comprobar si alguno de sus vecinos es negro
                if (i > 0 && image[(i - 1) * width + j] == 0) {
                    perimeter++;
                }
                if (i < height - 1 && image[(i + 1) * width + j] == 0) {
                    perimeter++;
                }
                if (j > 0 && image[i * width + j - 1] == 0) {
                    perimeter++;
                }
                if (j < width - 1 && image[i * width + j + 1] == 0) {
                    perimeter++;
                }
            }
        }
    }
    return perimeter;
}

// Función para calcular el área de una imagen
int calcArea(const int *image, int width, int height) {
    int area = 0;
	#pragma omp parallel for
    for (int i = 0; i < height; i++) {
		#pragma omp parallel for
        for (int j = 0; j < width; j++) {
            if (image[i * width + j] > 0) {
                area++;
            }
        }
    }
    return area;
}

// Función para calcular la redondez de una imagen
double calcRoundness(const int *image, int width, int height) {
    int perimeter = calcPerimeter(image, width, height);
    int area = calcArea(image, width, height);
    return (4.0 * M_PI * area) / (perimeter * perimeter);
}
//13.-solidity

  double calculateSolidity(double contourArea, double enclosingCircleRadius) {
    double enclosingCircleArea = M_PI * pow(enclosingCircleRadius, 2);
    return contourArea / enclosingCircleArea;
  }

