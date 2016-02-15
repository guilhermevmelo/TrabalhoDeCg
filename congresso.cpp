#include "congresso.h"
#include "objreader.h"

Congresso::Congresso() {
    ObjReader reader;

    color = Color(0.5, 0.5, 0.5, 0.3);
    reader.read("congresso2.obj", color);

    faces = reader.getFaces();
    bottomY = reader.getBottomY();
}
