#include "congresso.h"
#include "objreader.h"

Congresso::Congresso() {
    ObjReader reader;

    color = Color(0.5, 0.5, 0.5, 0.3);
    reader.read("/Users/guilherme/Developer/Trabalho/congresso2.obj", color);

    faces = reader.getFaces();
    bottomY = reader.getBottomY();
}


vector<Object *> Congresso::getFaces() {
    return faces;
}

double Congresso::getBottomY() {
    return bottomY;
}
