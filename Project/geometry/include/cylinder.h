#ifndef CYLINDER_H
#define CYLINDER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class Cylinder {
private:
    double radius, height;
    int resolution; // Number of points in the circular base
    vector<vector<double>> vertices;

public:
    Cylinder(double r, double h, int res);
    
    void generateVertices();
    void saveToFile(const string &filename);
    void plotCylinder(const string &filename);
    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);

};

#endif
