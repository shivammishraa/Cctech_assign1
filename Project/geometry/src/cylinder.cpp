#include "cylinder.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

Cylinder::Cylinder(double r, double h, int res) : radius(r), height(h), resolution(res) {
    generateVertices();
}

void Cylinder::generateVertices() {
    double angleStep = 2 * M_PI / resolution;

    // Bottom circle
    for (int i = 0; i < resolution; i++) {
        double x = radius * cos(i * angleStep);
        double y = radius * sin(i * angleStep);
        vertices.push_back({x, y, 0});
    }

    // Top circle
    for (int i = 0; i < resolution; i++) {
        double x = radius * cos(i * angleStep);
        double y = radius * sin(i * angleStep);
        vertices.push_back({x, y, height});
    }
}

void Cylinder::saveToFile(const string &filename) const {
    ofstream file(filename, ios::app); // Open in append mode
    if (!file) {
        cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    // Write bottom circle edges
    for (int i = 0; i < resolution; i++) {
        int next = (i + 1) % resolution;
        file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << "\n";
        file << vertices[next][0] << " " << vertices[next][1] << " " << vertices[next][2] << "\n";
    }
   file<<"\n";
    // Write top circle edges
    for (int i = resolution; i < 2 * resolution; i++) {
        int next = (i + 1) % resolution + resolution;
        file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << "\n";
        file << vertices[next][0] << " " << vertices[next][1] << " " << vertices[next][2] << "\n";
    }

    // Write vertical edges
    // for (int i = 0; i < resolution; i++) {
    //     file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << "\n\n";
    //     file << vertices[i + resolution][0] << " " << vertices[i + resolution][1] << " " << vertices[i + resolution][2] << "\n\n";
    // }

    file.close();
}

void Cylinder::plot(const string &filename) const {
    saveToFile(filename);

    string command = 
        "gnuplot -p -e \""
        "set terminal wxt; "
        "set xlabel 'X'; "
        "set ylabel 'Y'; "
        "set zlabel 'Z'; "
        "splot '" + filename + "' with linespoints pointtype 7 linecolor 'black'\"";
    system(command.c_str());
}

void Cylinder::translate(double dx, double dy, double dz) {
    for (auto &v : vertices) {
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
    }
}

void Cylinder::rotate(double angle, char axis) {
    double radians = angle * M_PI / 180.0;

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
}

void Cylinder::scale(double sx, double sy, double sz) {
    for (auto& v : vertices) {
        v[0] *= sx;
        v[1] *= sy;
        v[2] *= sz;
    }
}