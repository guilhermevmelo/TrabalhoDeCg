#include "object.h"

Object::Object() {
    color = Color(0, 0, 0, 0);
}

vector<Primitive *> Object::getFaces() {
    return faces;
}

double Object::getBottomY() {
    return bottomY;
}

Color Object::getColor() { return color; }


void Object::translate(double tx, double ty, double tz) {
    for(unsigned int i = 0; i < faces.size(); i++) {
        faces.at(i)->translate(tx, ty, tz);
    }
}

void Object::scale(double sx, double sy, double sz) {
    for(unsigned int i = 0; i < faces.size(); i++) {
        faces.at(i)->scale(sx, sy, sz);
    }
}

void Object::rotateX(double angle) {
    for(unsigned int i = 0; i < faces.size(); i++) {
        faces.at(i)->rotateX(angle);
    }
}

void Object::rotateY(double angle) {
    for(unsigned int i = 0; i < faces.size(); i++) {
        faces.at(i)->rotateY(angle);
    }
}

void Object::rotateZ(double angle) {
    for(unsigned int i = 0; i < faces.size(); i++) {
        faces.at(i)->rotateZ(angle);
    }
}
