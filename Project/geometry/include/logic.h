#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <array>

using namespace std;

template<typename T, size_t N>
class Point {
public:
    array<T, N> coords;
    Point();
    void input();
};

template<typename T, size_t N>
class DataFile {
public:
    void generate(const Point<T, N>& p1, const Point<T, N>& p2);
    void generatePolyline(int numPoints);
    void translatePolyline(int numPoints, const array<T, N>& displacement);
};

template<typename T, size_t N>
class GnuPlotting {
public:
    void plot();
    void plotTranslated();
};

// Function declarations for cuboid operations
void translateCuboid(double dx, double dy, double dz);
void plotCuboid();
void plotTranslatedCuboid();
void plotTranslatedPolyline();

// Explicit template instantiations for double precision (2D and 3D)
extern template class Point<double, 2>;
extern template class Point<double, 3>;
extern template class DataFile<double, 2>;
extern template class DataFile<double, 3>;
extern template class GnuPlotting<double, 2>;
extern template class GnuPlotting<double, 3>;


#endif
