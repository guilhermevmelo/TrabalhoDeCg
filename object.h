#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <vector>
#include "color.h"
#include "ray.h"
#include "primitive.h"

using namespace std;

class Object {

    protected:
        Color color;
        vector<Primitive*> faces;
        double bottomY;

    public:
        Object();

        vector<Primitive *> getFaces();
        double getBottomY();
        Color getColor();

        void translate(double tx, double ty, double tz);
        void scale(double sx, double sy, double sz);
        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);
};

#endif // OBJECT_H
