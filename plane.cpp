#include "plane.h"

Plane::Plane() {
    normal = Vector(1, 0, 0);
    distance = 0;
    material = Material();
}

Plane::Plane(Vector n, double d, Material material):normal(n), distance(d){
    this->material = material;
}


double Plane::findIntersection(Ray ray) {
    Vector ray_direction = ray.direction();

    double a = ray_direction.dotProduct(normal);

    if (a == 0) {
        // Raio paralelo ao plano
        return -1;
    }
    double b = normal.dotProduct(ray.origin().add(normal.multiply(distance).negative()));
    return -1*b/a;

}

void Plane::translate(double tx, double ty, double tz) {

}

void Plane::scale(double sx, double sy, double sz) {

}

void Plane::rotateX(double angle) {

}

void Plane::rotateY(double angle) {

}

void Plane::rotateZ(double angle) {

}
