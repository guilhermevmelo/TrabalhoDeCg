#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

class Camera {
    Vector camera_position, camera_direction, camera_right, camera_down;
public:
    Camera();
    Camera(Vector, Vector, Vector, Vector);

    Vector getCameraPosition() { return camera_position; }
    Vector getCameraDirection() { return camera_direction; }
    Vector getCameraRight() { return camera_right; }
    Vector getCameraDown() { return camera_down; }
};

#endif // CAMERA_H
