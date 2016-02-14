#include "vector.h"

Vector::Vector() {
    _x = 0;
    _y = 0;
    _z = 0;
}

Vector::Vector(double x, double y, double z): _x(x), _y(y), _z(z){}

Vector Vector::normalize() {
    double m = magnitude();
    return Vector(_x/m, _y/m, _z/m);
}

double Vector::magnitude() {
    return sqrt(_x*_x + _y*_y + _z*_z);
}

Vector Vector::negative() {
    return Vector(-_x, -_y, -_z);
}

double Vector::dotProduct(Vector v) {
    return _x*v.x() + _y*v.y() + _z*v.z();
}

Vector Vector::crossProduct(Vector v) {
    return Vector(_y*v.z() - _z*v.y(),
                  _z*v.x() - _x*v.z(),
                  _x*v.y() - _y*v.x());
}

Vector Vector::add(Vector v) {
    return Vector(_x + v.x(), _y + v.y(), _z+v.z());
}

Vector Vector::multiply(double scalar) {
    return Vector(_x * scalar, _y * scalar, _z * scalar);
}


ostream & operator<<(ostream & out, Vector &vetor) {
    out <<"[" << vetor.x();
    out << ", " << vetor.y();
    out << ", " << vetor.z();
    out << "]";
    return out;
}

void Vector::translate(double tx, double ty, double tz) {
    _x += tx;
    _y += ty;
    _z += tz;
}

void Vector::scale(double sx, double sy, double sz) {
    _x *= sx;
    _y *= sy;
    _z *= sz;
}

void Vector::rotateX(double angle) {
    double newY = _y*cos(angle) - _z*sin(angle);
    double newZ = _y*sin(angle) + _z*cos(angle);

    _y = newY;
    _z = newZ;
}

void Vector::rotateY(double angle) {
    double newX = _x*cos(angle) + _z*sin(angle);
    double newZ = (-_x)*sin(angle) + _z*cos(angle);

    _x = newX;
    _z = newZ;
}

void Vector::rotateZ(double angle) {
    double newX = _x*cos(angle) - _y*sin(angle);
    double newY = _x*sin(angle) + _y*cos(angle);

    _x = newX;
    _y = newY;
}
