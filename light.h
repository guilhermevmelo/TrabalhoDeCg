#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "color.h"

class Light {
    Vector position;
    Color color;
public:
    Light();
    Light(Vector, Color);

    Vector pos() { return position; }
    Color col() { return color; }
};

#endif // LIGHT_H
