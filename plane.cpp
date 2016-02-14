#include "plane.h"

Plane::Plane() {
    normal = Vector(1, 0, 0);
    distance = 0;
    color = Color(0.5, 0.5, 0.5, 0);
}

Plane::Plane(Vector n, double d, Color c):normal(n), distance(d), color(c){}


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
