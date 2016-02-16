#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "material.h"
#include "ray.h"

class Primitive {
    protected:
        Material material;
    public:
        Primitive();

        Material getMaterial() { return material; }
        virtual double findIntersection(Ray ray) = 0;
        virtual Vector getNormalAt(Vector p) = 0;

        virtual void translate(double tx, double ty, double tz) = 0;
        virtual void scale(double sx, double sy, double sz) = 0;
        virtual void rotateX(double angle) = 0;
        virtual void rotateY(double angle) = 0;
        virtual void rotateZ(double angle) = 0;
};

#endif // PRIMITIVE_H
