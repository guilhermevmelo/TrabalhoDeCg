#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera {
    Vector camera_position, camera_direction, camera_right, camera_down;

    public:
        Camera(Vector, Vector, Vector);

        Ray createRay(double, double);

        Vector getCameraPosition() { return camera_position; }
        Vector getCameraDirection() { return camera_direction; }
        Vector getCameraRight() { return camera_right; }
        Vector getCameraDown() { return camera_down; }
};

#endif // CAMERA_H
