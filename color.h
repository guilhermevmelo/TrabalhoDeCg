#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

class Color {
    double red, green, blue, special; // Special é a reflectividade e o polimento
public:
    Color();
    Color(double, double, double, double);

    double r() { return red; }
    double g() { return green; }
    double b() { return blue; }
    double s() { return special; }
    void r(double value){ red = value; }
    void g(double value){ green = value; }
    void b(double value){ blue = value; }

    double brightness() { return (red + green + blue)/3; }
    Color scale(double);
    Color add(Color c);
    Color multiply(Color c);
    Color average(Color color);
    Color clip();
};


//Usar para debugar
std::ostream& operator<<(std::ostream& out, Color &color);

#endif // COLOR_H
