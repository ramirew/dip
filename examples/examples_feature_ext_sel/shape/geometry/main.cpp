#include "libreriaGeometria.h"
#include <iostream>
#include <vector>

int main() {
    // Ejemplo de imagen con intensidades de pixels [10, 20, 30, 40, 50]
    std::vector<Pixel> pixels = {{10}, {20}, {30}, {40}, {50}};
    int width = 1, height = 5;

    ImageAsymmetry imageAsymmetry;
    double asymmetry = imageAsymmetry.find(pixels, width, height);

    std::cout << "Asimetría: "
}