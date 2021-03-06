#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

using namespace std;

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

    void translate(double tx, double ty, double tz);
    void scale(double sx, double sy, double sz);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
};

//Usar para debugar
std::ostream& operator<<(std::ostream& out, Vector &vector);

#endif // VECTOR_H
