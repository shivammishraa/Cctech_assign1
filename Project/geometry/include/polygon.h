#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>

using namespace std;

class Polygon {
private:
    vector<vector<double>> vertices; // Stores (x, y, z) coordinates
    void calculateCentroid(double &cx, double &cy, double &cz); // Helper function

public:
    Polygon(int sides); // Constructor

    void addVertex(double x, double y, double z);
    void plotPolygon(const string &filename);

    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);
    void saveToFile(const std::string& filename) const;
};

#endif // POLYGON_H
