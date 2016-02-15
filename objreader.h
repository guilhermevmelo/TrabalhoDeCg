#ifndef OBJREADER_H
#define OBJREADER_H

#include<vector>
#include "object.h"
#include "primitive.h"

class ObjReader {
    double bottomY;
    vector<Primitive *> faces;

    public:
        ObjReader();
        int read(const char* filename, Color color);
        double getBottomY();
        vector<Primitive *> getFaces();
};

#endif // OBJREADER_H
