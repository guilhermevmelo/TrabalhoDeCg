#include "triangle.h"

Triangle::Triangle() {
    _a = Vector(1,0,0);
    _b = Vector(0,1,0);
    _c = Vector(0,0,1);
    _color = Color(0.5,0.5,0.5,0);
}

Triangle::Triangle(Vector a, Vector b, Vector c, Color color):_a(a), _b(b), _c(c), _color(color) { }

Vector Triangle::getNormal() {
    Vector ca(_c.x() - _a.x(), _c.y() - _a.y(), _c.z() - _a.z());
    Vector ba(_b.x() - _a.x(), _b.y() - _a.y(), _b.z() - _a.z());
    return ca.crossProduct(ba).normalize();
}

double Triangle::getDistance() {
    Vector normal = getNormal();
    return normal.dotProduct(_a);
}

Color Triangle::getColor() {
    return _color;
}

double Triangle::findIntersection(Ray ray) {
    Vector ray_direction = ray.direction();
    Vector ray_origin = ray.origin();

    Vector normal = getNormal();
    double distance = getDistance();

    double a = ray_direction.dotProduct(normal);

    if (a == 0) {
        // Raio paralelo ao triangulo
        return -1;
    }

    double b = normal.dotProduct(ray.origin().add(normal.multiply(distance).negative()));
    double distance2plane = -1*b/a;

    double Qx = ray_direction.multiply(distance2plane).x() + ray_origin.x();
    double Qy = ray_direction.multiply(distance2plane).y() + ray_origin.y();
    double Qz = ray_direction.multiply(distance2plane).z() + ray_origin.z();

    Vector Q(Qx, Qy, Qz);

    //[CAxQA] * N >= 0
    Vector CA(_c.x() - _a.x(), _c.y() - _a.y(), _c.z() - _a.z());
    Vector QA(Q.x() - _a.x(), Q.y() - _a.y(), Q.z() - _a.z());

    double test1 = (CA.crossProduct(QA)).dotProduct(normal);

    //[BCxQC] * N >= 0
    Vector BC(_b.x() - _c.x(), _b.y() - _c.y(), _b.z() - _c.z());
    Vector QC(Q.x() - _c.x(), Q.y() - _c.y(), Q.z() - _c.z());

    double test2 = (BC.crossProduct(QC)).dotProduct(normal);

    //[ABxQB] * N >= 0

    Vector AB(_a.x() - _b.x(), _a.y() - _b.y(), _a.z() - _b.z());
    Vector QB(Q.x() - _b.x(), Q.y() - _b.y(), Q.z() - _b.z());

    double test3 = (AB.crossProduct(QB)).dotProduct(normal);

    if(test1 >= 0  && test2 >= 0  && test3 >= 0  ) {
        //dentro do triangulo
        return -1*b/a;
    } else {
        //fora do triangulo
        return -1;
    }
}

void Triangle::translate(double tx, double ty, double tz) {
    _a.translate(tx, ty, tz);
    _b.translate(tx, ty, tz);
    _c.translate(tx, ty, tz);
}

void Triangle::scale(double sx, double sy, double sz) {
    _a.scale(sx, sy, sz);
    _b.scale(sx, sy, sz);
    _c.scale(sx, sy, sz);
}

void Triangle::rotateX(double angle) {
    _a.rotateX(angle);
    _b.rotateX(angle);
    _c.rotateX(angle);
}

void Triangle::rotateY(double angle) {
    _a.rotateY(angle);
    _b.rotateY(angle);
    _c.rotateY(angle);
}

void Triangle::rotateZ(double angle) {
    _a.rotateY(angle);
    _b.rotateY(angle);
    _c.rotateY(angle);
}

