#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>
#include "shape.h"

class Polygon : public Shape {
private:
    std::vector<std::vector<double>> vertices; // Stores (x, y, z) coordinates
    void calculateCentroid(double &cx, double &cy, double &cz); // Helper function

public:
    Polygon(int sides); // Constructor

    void addVertex(double x, double y, double z);
    void plot(const std::string& filename) const override; // Override plot method
    void saveToFile(const std::string& filename) const override;

    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);

    // Additional method
    void plotPolygon(const std::string& filename) const; // Specific plot method
};

#endif // POLYGON_H
