#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <array>

using namespace std;

// Template class for Points
template<typename T, size_t N>
class point {
public:
    array<T, N> coords;
    point();
    void input();
};

// Template class for DataFile
template<typename T, size_t N>
class DataFile {
public:
    void generate(const point<T, N>& p1, const point<T, N>& p2);
};

// Template class for GnuPlotting
template<typename T, size_t N>
class GnuPlotting {
public:
    void plot();
};

// Explicit template instantiations (to be implemented in logic.cpp)
extern template class point<double, 2>;
extern template class point<double, 3>;
extern template class DataFile<double, 2>;
extern template class DataFile<double, 3>;
extern template class GnuPlotting<double, 2>;
extern template class GnuPlotting<double, 3>;

#endif // LOGIC_H
