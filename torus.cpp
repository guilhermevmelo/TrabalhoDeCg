#include "torus.h"
#include "objreader.h"

Torus::Torus() {
    ObjReader reader;

    color = Color(0.94, 0.75, 0.31, 0);
    reader.read("torus.obj", color);

    faces = reader.getFaces();
    bottomY = reader.getBottomY();
}

