#ifndef STL_SHAPE_H
#define STL_SHAPE_H

#include <string>
#include <vector>

class STLShape {
private:
    std::vector<std::vector<double>> vertices; // Stores (x, y, z) coordinates

public:
    STLShape(const std::string& filepath); // Constructor to parse the STL file
    void saveToFile(const std::string& filename) const; // Save vertices to a .dat file
    void plot(const std::string& filename) const; // Plot the shape using GNUPLOT
};

#endif 