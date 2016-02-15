#include "camera.h"

Camera::Camera(Vector position, Vector look_at, Vector up):camera_position(position), camera_direction(look_at) {
    Vector diff_btw (camera_position.x() - look_at.x(),
                     camera_position.y() - look_at.y(),
                     camera_position.z() - look_at.z());

    camera_direction = diff_btw.negative().normalize();
    camera_right = camera_direction.crossProduct(up).normalize();
    camera_down = camera_right.crossProduct(camera_direction);
}

Ray Camera::createRay(double xamnt, double yamnt) {
    Vector camera_ray_direction = camera_direction.add(camera_right.multiply(xamnt - 0.5).add(camera_down.multiply(yamnt - 0.5))).normalize();

    Ray camera_ray(camera_position, camera_ray_direction);
    return camera_ray;
}
