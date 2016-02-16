#include "light.h"

Light::Light() {
    position = Vector(0, 0, 0);
    color_a = Color(1, 1, 1);
    color_d = Color(1, 1, 1);
    color_s = Color(1, 1, 1);
}

Light::Light(Vector p, Color ca, Color cd, Color cs):position(p), color_a(ca), color_d(cd), color_s(cs){}
