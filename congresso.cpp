#include "congresso.h"
#include "objreader.h"

Congresso::Congresso() {
    ObjReader reader;

    material = Material();
    reader.read("/Users/guilherme/Developer/Trabalho/congresso2.obj", material);

    faces = reader.getFaces();
    bottomY = reader.getBottomY();
}
