#ifndef CUBE_H
#define CUBE_H

#include "vector"
#include "object.h"

class Cube : public Object {
    vector<Object *> faces;
    Color _color;

public:
    Cube(Vector, Vector, Color);

    vector<Object *> getFaces() {return faces;}

    virtual Color getColor();
    virtual double findIntersection(Ray ray);

    virtual void translate(double tx, double ty, double tz);
    virtual void scale(double sx, double sy, double sz);
    virtual void rotateX(double angle);
    virtual void rotateY(double angle);
    virtual void rotateZ(double angle);
};

#endif // CUBE_H
