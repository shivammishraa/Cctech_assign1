#ifndef POLYLINE_H
#define POLYLINE_H

#include <vector>
#include <string>

using namespace std;

class Polyline {
private:
    vector<vector<double>> points; // Stores (x, y, z) coordinates

public:
    Polyline();  // Constructor

    void addPoint(double x, double y, double z);  // Add a point
    void plotPolyline(const string& filename);  // Save & Plot

    void translate(double dx, double dy, double dz);  // Translation
    void scale(double sx, double sy, double sz);  // Scaling
    void rotate(double angle, char axis);  // Rotation

    void saveToFile(const string& filename);  // Save to file
    void loadFromFile(const string& filename);  // Load from file
};

#endif
