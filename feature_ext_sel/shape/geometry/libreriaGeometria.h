#ifndef LIBRERIAGEOMETRIA_H_INCLUDED
#define LIBRERIAGEOMETRIA_H_INCLUDED

const double PI = 3.14159265358979323846;

class Circle {
public:
    Circle(double r);
    double getArea();
    double getPerimeter();
private:
    double radius;
};

#endif // LIBRERIAGEOMETRIA_H_INCLUDED

