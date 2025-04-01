#include "triangle.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

Triangle::Triangle(double x1, double y1, double z1,
                   double x2, double y2, double z2,
                   double x3, double y3, double z3) {
    vertices = {{x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3}};
}

void Triangle::translate(double dx, double dy, double dz) {
    for (auto& v : vertices) {
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
    }
}

void Triangle::scale(double sx, double sy, double sz) {
    for (auto& v : vertices) {
        v[0] *= sx;
        v[1] *= sy;
        v[2] *= sz;
    }
}

void Triangle::rotate(double angle, char axis, double Px, double Py, double Pz) {
    double radians = angle * M_PI / 180.0;

    // Step 1: Translate to origin
    translate(-Px, -Py, -Pz);

    // Step 2: Rotate around origin
    for (auto& v : vertices) {
        double x = v[0], y = v[1], z = v[2];

        if (axis == 'x') {
            v[1] = y * cos(radians) - z * sin(radians);
            v[2] = y * sin(radians) + z * cos(radians);
        } else if (axis == 'y') {
            v[0] = x * cos(radians) + z * sin(radians);
            v[2] = -x * sin(radians) + z * cos(radians);
        } else if (axis == 'z') {
            v[0] = x * cos(radians) - y * sin(radians);
            v[1] = x * sin(radians) + y * cos(radians);
        }
    }

    // Step 3: Translate back to original position
    translate(Px, Py, Pz);
}

void Triangle::plotTriangle(const string& filename) const { // Marked as const
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Write triangle vertices
    for (const auto& v : vertices) {
        file << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    file << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n"; // Close the triangle
    file.close();

    // Use GNUPLOT to plot the triangle
    string command = 
    "gnuplot -p -e \""
    "set terminal wxt; "
    "set xlabel 'X'; "
    "set ylabel 'Y'; "
    "set zlabel 'Z'; "
    "set view equal xyz; "
    "splot '" + filename + "' with linespoints pointtype 7 linecolor 'red'\"";

    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to execute GNUPLOT command." << endl;
    }
}

void Triangle::saveToFile(const string &filename) const {
    ofstream file(filename, ios::app); // Open in append mode
    if (!file) {
        cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    for (size_t i = 0; i < vertices.size(); i++) {
        size_t next = (i + 1) % vertices.size();
        file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << "\n";
        file << vertices[next][0] << " " << vertices[next][1] << " " << vertices[next][2] << "\n\n";
    }

    file.close();
}

void Triangle::plot(const std::string& filename) const {
    plotTriangle(filename); // Use the existing plotTriangle methodhod
}