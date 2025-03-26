#ifndef SPHERE_H
#define SPHERE_H

#include "logic.h"
#include <vector>
#include <fstream>
#include <cmath>

template <class T>
class Sphere {
private:
    T radius;
    Point<T, 3> center;
    int latSegments; // Number of latitude segments
    int lonSegments; // Number of longitude segments
    std::vector<Point<T, 3>> points; // Stores points on the sphere

public:
    Sphere(T radius, const Point<T, 3>& center, int latSegments, int lonSegments)
        : radius(radius), center(center), latSegments(latSegments), lonSegments(lonSegments) {
        generateSphere();
    }

    void generateSphere();
    void translate(T dx, T dy, T dz);
    void scale(T factor);
    void writeToFile(const std::string& filename) const;
};

#endif