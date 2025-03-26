#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <fstream>
#include "../include/logic.h"

// Cuboid Class
template<typename T>
class Cuboid {
public:
    Point<T, 3> origin;
    T length, breadth, height;

    Cuboid(Point<T, 3> origin, T length, T breadth, T height);
    void generate();
    void translate(T dx, T dy, T dz);
};

// Cylinder Class
template<typename T>
class Cylinder {
public:
    T radius, height;
    int segments;
    Point<T, 3> center;

    Cylinder(T radius, T height, int segments, const Point<T, 3>& center);
    void generateCylinder();
    void translate(T dx, T dy, T dz);
    void rotate(T angleDeg, char axis);
    void scale(T factor);
};

// Sphere Class
template<typename T>
class Sphere {
public:
    T radius;
    Point<T, 3> center;
    int latSegments; // Number of latitude segments
    int lonSegments; // Number of longitude segments

    Sphere(T radius, const Point<T, 3>& center, int latSegments, int lonSegments);
    void generateSphere();
    void translate(T dx, T dy, T dz);
    void scale(T factor);
    void writeToFile(const std::string& filename) const;
};

#endif // SHAPES_H