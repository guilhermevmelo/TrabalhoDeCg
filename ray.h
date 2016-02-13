#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
    Vector _origin, _direction;

public:
    Ray();
    Ray(Vector, Vector);

    Vector origin() { return _origin; }
    Vector direction() { return _direction; }
};

#endif // RAY_H
