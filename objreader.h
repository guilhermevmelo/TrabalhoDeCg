#ifndef OBJREADER_H
#define OBJREADER_H

#include<vector>
#include<cmath>
#include "object.h"

class ObjReader {
    double bottomY;
    vector<Object*> faces;

    public:
        ObjReader();
        int read(const char* filename, Color color);
        double getBottomY();
        vector<Object *> getFaces();
};

#endif // OBJREADER_H
