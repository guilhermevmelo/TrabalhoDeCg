#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include "primitive.h"
#include "vector.h"
#include "color.h"

class Triangle : public Primitive {
    Vector _a, _b, _c, _n;

public:
    Triangle();
    Triangle(Vector, Vector, Vector, Material);
    Triangle(Vector, Vector, Vector, Material, Vector);

    Vector getNormal();
    double getDistance();

    virtual Vector getNormalAt(Vector p);
    virtual double findIntersection(Ray ray);

    virtual void translate(double tx, double ty, double tz);
    virtual void scale(double sx, double sy, double sz);
    virtual void rotateX(double angle);
    virtual void rotateY(double angle);
    virtual void rotateZ(double angle);
};
#endif // TRIANGLE_H
