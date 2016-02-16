#include "material.h"

Material::Material() {
    _ka = Color(0.1, 0.1, 0.1);
    _kd = Color(0.5, 0.5, 0.5);
    _ks = Color(0.5, 0.5, 0.5);
    _m = 20;
}

Material::Material(Color ka, Color kd, Color ks, double m):_ka(ka),_kd(kd), _ks(ks), _m(m) {}
