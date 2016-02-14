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

    virtual void translate(double tx, double ty, double tz) {}
    virtual void scale(double sx, double sy, double sz){}
    virtual void rotateX(double angle){}
    virtual void rotateY(double angle){}
    virtual void rotateZ(double angle){}
};

#endif // OBJECT_H
