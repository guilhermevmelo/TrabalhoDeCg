#ifndef CONGRESSO_H
#define CONGRESSO_H

#include "object.h"
#include "objreader.h"
#include "color.h"

class Congresso : public Object {
    Color color;
    vector<Object*> faces;
    double bottomY;

    public:
        Congresso();
        vector<Object *> getFaces();
        double getBottomY();
};

#endif // CONGRESSO_H
