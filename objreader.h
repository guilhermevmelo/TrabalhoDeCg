#ifndef OBJREADER_H
#define OBJREADER_H

#include<vector>
#include "object.h"
#include "primitive.h"
#include "material.h"

class ObjReader {
    double bottomY;
    vector<Primitive *> faces;

    public:
        ObjReader();
        int read(const char* filename, Material material);
        double getBottomY();
        vector<Primitive *> getFaces();
};

#endif // OBJREADER_H
