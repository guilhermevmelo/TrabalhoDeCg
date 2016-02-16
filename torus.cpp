#include "torus.h"
#include "objreader.h"

Torus::Torus() {
    ObjReader reader;

    material = Material();
    reader.read("/Users/guilherme/Developer/Trabalho/chico.obj", material);

    faces = reader.getFaces();
    bottomY = reader.getBottomY();
}

