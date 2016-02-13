#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "object.h"
#include "vector.h"
#include "color.h"

class Sphere : public Object {
    Vector center;
    double radius;
    Color color;

public:
    Sphere();
    Sphere(Vector, double, Color);

    Vector getCenter() { return center; }
    double rad() { return radius; }
    virtual Color getColor() { return color; }

    Vector getNormalAt(Vector p);
    virtual double findIntersection(Ray ray);
};

#endif // SPHERE_H
