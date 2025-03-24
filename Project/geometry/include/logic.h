#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <array>

using namespace std;

// Template class for Points
template<typename T, size_t N>
class Point {
public:
    array<T, N> coords;
    Point();
    void input();
};

// Template class for DataFile
template<typename T, size_t N>
class DataFile {
public:
    void generate(const Point<T, N>& p1, const Point<T, N>& p2);
};

// Template class for GnuPlotting
template<typename T, size_t N>
class GnuPlotting {
public:
    void plot();
};

// Function to plot cuboids (implemented in logic.cpp)
void plotCuboid();

// Explicit template instantiations
extern template class Point<double, 2>;
extern template class Point<double, 3>;
extern template class DataFile<double, 2>;
extern template class DataFile<double, 3>;
extern template class GnuPlotting<double, 2>;
extern template class GnuPlotting<double, 3>;

#endif // LOGIC_H
