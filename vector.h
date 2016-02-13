#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector {
    double _x, _y, _z;
public:
    Vector();
    Vector(double, double, double);

    double x() { return _x; }
    double y() { return _y; }
    double z() { return _z; }

    double magnitude();
    Vector normalize();
    Vector negative();
    double dotProduct(Vector v);
    Vector crossProduct(Vector v);
    Vector add(Vector v);
    Vector multiply(double scalar);
};

#endif // VECTOR_H
