#include "libreriaGeometria.h"
#include <iostream>
#include <cmath>

Circle::Circle(double r) {
    radius = r;
}

double Circle::getArea() {
    return PI * pow(radius, 2);
}

double Circle::getPerimeter() {
    return 2 * PI * radius;
}