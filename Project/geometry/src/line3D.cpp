#include "line3D.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

// Constructor to initialize the two endpoints of the line
Line3D::Line3D() {
    points.resize(2, vector<double>(3, 0.0));
}

// Set the two endpoints of the line
void Line3D::setPoints(double x1, double y1, double z1, double x2, double y2, double z2) {
    points[0] = {x1, y1, z1};
    points[1] = {x2, y2, z2};
}

// Plot the line
void Line3D::plotLine(const string &filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << "\n";
        return;
    }

    for (const auto &p : points) {
        file << p[0] << " " << p[1] << " " << p[2] << "\n";
    }
    file.close();

    string command = 
        "gnuplot -p -e \""
        "set terminal wxt; "
        "set xlabel 'X'; "
        "set ylabel 'Y'; "
        "set zlabel 'Z'; "
        "splot '" + filename + "' with linespoints pointtype 7 linecolor 'blue'\"";

    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to execute GNUPLOT command.\n";
    }
}

// translating the line
void Line3D::translate(double dx, double dy, double dz) {
    for (auto &p : points) {
        p[0] += dx;
        p[1] += dy;
        p[2] += dz;
    }
}

//scaling the line
void Line3D::scale(double sx, double sy, double sz) {
    for (auto &p : points) {
        p[0] *= sx;
        p[1] *= sy;
        p[2] *= sz;
    }
}

// Rotate the line 
void Line3D::rotate(double angle, char axis) {
    double radians = angle * M_PI / 180.0;
    double cx = (points[0][0] + points[1][0]) / 2.0;
    double cy = (points[0][1] + points[1][1]) / 2.0;
    double cz = (points[0][2] + points[1][2]) / 2.0;

    for (auto &p : points) {
        double x = p[0] - cx, y = p[1] - cy, z = p[2] - cz;
        if (axis == 'x') {
            p[1] = cy + y * cos(radians) - z * sin(radians);
            p[2] = cz + y * sin(radians) + z * cos(radians);
        } else if (axis == 'y') {
            p[0] = cx + x * cos(radians) + z * sin(radians);
            p[2] = cz - x * sin(radians) + z * cos(radians);
        } else if (axis == 'z') {
            p[0] = cx + x * cos(radians) - y * sin(radians);
            p[1] = cy + x * sin(radians) + y * cos(radians);
        }
    }
}
