#include "ray.h"

Ray::Ray() {
    _origin = Vector(0, 0, 0);
    _direction = Vector(1, 0, 0);
}

Ray::Ray(Vector o, Vector d): _origin(o), _direction(d){}

