#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Triangle {
private:
    vector<vector<double>> vertices; // 3 vertices, each with (x, y, z)

public:
    Triangle(double x1, double y1, double z1,
             double x2, double y2, double z2,
             double x3, double y3, double z3);

    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis, double Px, double Py, double Pz);
    void plotTriangle(const string& filename);
};

#endif
