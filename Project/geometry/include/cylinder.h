#ifndef CYLINDER_H
#define CYLINDER_H

#include "logic.h"
#include <vector>

template <class T>
class Cylinder {
private:
    T radius, height;
    int segments;
    Point<T, 3> center;
    std::vector<Point<T, 3>> baseCircle; // Stores points of the base circle
    std::vector<Point<T, 3>> topCircle;  // Stores points of the top circle

public:
    Cylinder(T radius, T height, int segments, const Point<T, 3>& center)
        : radius(radius), height(height), segments(segments), center(center) {
        baseCircle.resize(segments); // Allocate memory for baseCircle
        topCircle.resize(segments); // Allocate memory for topCircle
        generateCylinder();
    }

    void generateCylinder();
    void translate(T dx, T dy, T dz);
    void rotate(T angleDeg, char axis); // Updated declaration to include axis
    void scale(T factor);
};

#endif