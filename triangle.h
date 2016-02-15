#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include "object.h"
#include "vector.h"
#include "color.h"

class Triangle : public Object {
    Vector _a, _b, _c, _n;
    Color _color;

public:
    Triangle();
    Triangle(Vector, Vector, Vector, Color);
    Triangle(Vector, Vector, Vector, Color, Vector);

    Vector getNormal();
    double getDistance();

    virtual Vector getNormalAt(Vector p);
    virtual Color getColor();
    virtual double findIntersection(Ray ray);

    virtual void translate(double tx, double ty, double tz);
    virtual void scale(double sx, double sy, double sz);
    virtual void rotateX(double angle);
    virtual void rotateY(double angle);
    virtual void rotateZ(double angle);
};
#endif // TRIANGLE_H
