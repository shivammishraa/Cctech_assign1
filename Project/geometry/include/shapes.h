#ifndef SHAPES_H
#define SHAPES_H

#include "../include/logic.h"

// Template class for Cuboid
template<typename T>
class Cuboid {
private:
    Point<T, 3> origin;
    T length, breadth, height;
public:
    Cuboid(Point<T, 3> origin, T length, T breadth, T height);
    void generate();
};

// Explicit template instantiation
extern template class Cuboid<double>;

#endif // SHAPES_H
