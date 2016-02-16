#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "color.h"

class Light {
    Vector position;
    Color color_a;
    Color color_d;
    Color color_s;
public:
    Light();
    Light(Vector, Color, Color, Color);

    Vector pos() { return position; }
    Color col_a() { return color_a; }
    Color col_d() { return color_d; }
    Color col_s() { return color_s; }
};

#endif // LIGHT_H
