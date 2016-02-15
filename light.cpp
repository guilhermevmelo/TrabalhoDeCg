#include "light.h"

Light::Light() {
    position = Vector(0, 0, 0);
    color = Color(1, 1, 1, 0);
}

Light::Light(Vector p, Color c):position(p), color(c){}
