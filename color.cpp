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

Color Color::average(Color color) {
    return Color ((red + color.r())/2, (green + color.g())/2, (blue + color.b())/2, special);
}

Color Color::clip() {
        double alllight = red + green + blue;
        double excesslight = alllight - 3;
        if (excesslight > 0) {
            red = red + excesslight*(red/alllight);
            green = green + excesslight*(green/alllight);
            blue = blue + excesslight*(blue/alllight);
        }
        if (red > 1) {red = 1;}
        if (green > 1) {green = 1;}
        if (blue > 1) {blue = 1;}
        if (red < 0) {red = 0;}
        if (green < 0) {green = 0;}
        if (blue < 0) {blue = 0;}

        return Color (red, green, blue, special);
    }

ostream & operator<<(ostream & out, Color &color) {
    out <<"[" << color.r();
    out << ", " << color.g();
    out << ", " << color.b();
    out << "; " << color.s();
    out << "]";
    return out;
}
