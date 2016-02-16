#ifndef PLANE_H
#define PLANE_H

#include <cmath>
#include "primitive.h"
#include "vector.h"
#include "color.h"

class Plane : public Primitive {
    Vector normal;
    double distance;

public:
    Plane();
    Plane(Vector, double, Material);

    Vector getNormal() { return normal; }
    double getDistance() { return distance; }

    virtual Vector getNormalAt(Vector p) { return normal; }
    virtual double findIntersection(Ray ray);

    virtual void translate(double tx, double ty, double tz);
    virtual void scale(double sx, double sy, double sz);
    virtual void rotateX(double angle);
    virtual void rotateY(double angle);
    virtual void rotateZ(double angle);
};

#endif // PLANE_H
