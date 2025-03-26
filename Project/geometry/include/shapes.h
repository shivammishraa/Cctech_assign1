#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <fstream>
#include "../include/logic.h"

template<typename T>
class Cuboid {
public:
    Point<T, 3> origin;
    T length, breadth, height;

    Cuboid(Point<T, 3> origin, T length, T breadth, T height);
    void generate();
    void translate(T dx, T dy, T dz);
};

#endif // SHAPES_H
