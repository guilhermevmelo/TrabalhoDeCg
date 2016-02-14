#ifndef PLANE_H
#define PLANE_H

#include <cmath>
#include "object.h"
#include "vector.h"
#include "color.h"

class Plane : public Object {
    Vector normal;
    double distance;
    Color color;

public:
    Plane();
    Plane(Vector, double, Color);

    Vector getNormal() { return normal; }
    double getDistance() { return distance; }
    virtual Color getColor() { return color; }

    virtual Vector getNormalAt(Vector p) { return normal; }
    virtual double findIntersection(Ray ray);
};

#endif // PLANE_H
