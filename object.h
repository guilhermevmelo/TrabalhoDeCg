#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <vector>
#include "material.h"
#include "ray.h"
#include "primitive.h"

using namespace std;

class Object {

    protected:
        Material material;
        vector<Primitive*> faces;
        double bottomY;

    public:
        Object();

        vector<Primitive *> getFaces();
        double getBottomY();
        Material getMaterial();

        void translate(double tx, double ty, double tz);
        void scale(double sx, double sy, double sz);
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);
};

#endif // OBJECT_H
