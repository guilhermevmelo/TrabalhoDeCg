#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material  {
    Color _ka, _kd, _ks;
    double _m;

    public:
    Material();
    Material(Color, Color, Color, double);

    Color ka() { return _ka; }
    Color kd() { return _kd; }
    Color ks() { return _ks; }
    double m() { return _m; }
};

#endif // MATERIAL_H
