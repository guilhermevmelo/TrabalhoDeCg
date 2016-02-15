#ifndef CUBE_H
#define CUBE_H

#include "vector"
#include "object.h"
#include "primitive.h"

class Cube : public Object {

public:
    Cube(Vector, Vector, Color);
};

#endif // CUBE_H
