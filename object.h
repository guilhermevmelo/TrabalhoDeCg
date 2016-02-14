#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include "color.h"
#include "ray.h"

class Object {
public:
    Object();

    virtual Color getColor() { return Color(0, 0, 0, 0); }
    virtual double findIntersection(Ray ray) { return 0; }
    virtual Vector getNormalAt(Vector p) { return p;}
};

#endif // OBJECT_H
