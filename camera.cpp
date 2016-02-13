#include "camera.h"

Camera::Camera() {
    camera_position = Vector(0, 0, 0);
    camera_direction = Vector(0, 0, 1);
    camera_right = Vector(0, 0, 0);
    camera_down = Vector(0, 0, 0);
}

Camera::Camera(Vector position, Vector direction, Vector right, Vector down):camera_position(position), camera_direction(direction), camera_right(right), camera_down(down){}

