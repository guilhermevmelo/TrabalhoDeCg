#include "sphere.h"

Sphere::Sphere() {
    center = Vector(0, 0, 0);
    radius = 1.0;
    color = Color(0.5, 0.5, 0.5, 0);
}

Sphere::Sphere(Vector center, double radius, Color color):center(center), radius(radius), color(color) {}

Vector Sphere::getNormalAt(Vector p) {
    // A normal sempre aponta pra longe do centro da esfera

    Vector normal_at_point = p.add(center.negative()).normalize();
    return normal_at_point;
}

double Sphere::findIntersection(Ray ray) {
    double a = 1;
    double b = (2 * (ray.origin().x() - center.x()) * ray.direction().x()) + 
               (2 * (ray.origin().y() - center.y()) * ray.direction().y()) +
               (2 * (ray.origin().z() - center.z()) * ray.direction().z());
    double c = pow(ray.origin().x() - center.x(), 2) +
               pow(ray.origin().y() - center.y(), 2) +
               pow(ray.origin().z() - center.z(), 2) - (radius*radius);
    double delta = b*b - 4*c;

    if (delta > 0) {
        // intersecta nos dois lados
        //x'
        double x_1 = ((-b) - sqrt(delta))/2 - 0.000001;

        if (x_1 > 0) {
            // x' é a menor raiz positiva
            return x_1;
        }

        //x''
        //double x_2 = ((-b) + sqrt(delta))/2 - 0.000001;
        double x_2 = sqrt(delta)/2 - 0.000001;

        return x_2;
    } else {
        //não intersecta
        return -1;
    }
}

void Sphere::translate(double tx, double ty, double tz) {
    center.translate(tx, ty, tz);
}

void Sphere::scale(double sx, double sy, double sz) {
    radius *= sx;
}

void Sphere::rotateX(double angle) {
    center.rotateX(angle);
}

void Sphere::rotateY(double angle) {
    center.rotateY(angle);
}

void Sphere::rotateZ(double angle) {
    center.rotateZ(angle);
}
