#include "color.h"

Color::Color(){
    red = 0.5;
    green = 0.5;
    blue = 0.5;
}

Color::Color(double R, double G, double B, double S):red(R), green(G), blue(B), special(S){}

Color Color::scale(double scalar) {
    return Color(red*scalar, green*scalar, blue*scalar, special);
}

Color Color::add(Color c) {
    return Color(red + c.r(), green + c.g(), blue + c.b(), special);
}

Color Color::multiply(Color c) {
    return Color(red * c.r(), green * c.g(), blue * c.b(), special);
}
