#include "cube.h"
#include "triangle.h"

Cube::Cube(Vector corner1, Vector corner2, Material color) {
    double c1x = corner1.x();
    double c1y = corner1.y();
    double c1z = corner1.z();

    double c2x = corner2.x();
    double c2y = corner2.y();
    double c2z = corner2.z();

    Vector A(c2x, c1y, c1z);
    Vector B(c2x, c1y, c2z);
    Vector C(c1x, c1y, c2z);

    Vector D(c2x, c2y, c1z);
    Vector E(c1x, c2y, c1z);
    Vector F(c1x, c2y, c2z);

    //left side
    faces.push_back(new Triangle(D, A, corner1, color));
    faces.push_back(new Triangle(corner1, B, A, color));

    //far side
    faces.push_back(new Triangle(corner2, B, A, color));
    faces.push_back(new Triangle(A, D, corner2, color));

    //right side
    faces.push_back(new Triangle(F, C, B, color));
    faces.push_back(new Triangle(B, corner2, F, color));

    //front side
    faces.push_back(new Triangle(E, corner1, C, color));
    faces.push_back(new Triangle(C, F, E, color));

    //top
    faces.push_back(new Triangle(D, E, F, color));
    faces.push_back(new Triangle(F, corner2, D, color));

    //bottom
    faces.push_back(new Triangle(corner1, A, B, color));
    faces.push_back(new Triangle(B, C, corner1, color));
}
