#ifndef LINE3D_H
#define LINE3D_H

#include <vector>
#include <string>

using namespace std;

class Line3D {
private:
    vector<vector<double>> points; // Stores two points (x, y, z)

public:
    Line3D(); // Constructor

    void setPoints(double x1, double y1, double z1, double x2, double y2, double z2);
    void plotLine(const string &filename);

    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);
    void saveToFile(const std::string& filename) const;
};

#endif // LINE3D_H
