#include "polygon.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

// Constructor to initialize  
Polygon::Polygon(int sides) {
    vertices.reserve(sides);
}

// adding a vertex to the polygon
void Polygon::addVertex(double x, double y, double z) {
    vertices.push_back({x, y, z});
}

// Calculate the centroid of the polygon
void Polygon::calculateCentroid(double &cx, double &cy, double &cz) {
    cx = cy = cz = 0;
    for (const auto &v : vertices) {
        cx += v[0];
        cy += v[1];
        cz += v[2];
    }
    cx /= vertices.size();
    cy /= vertices.size();
    cz /= vertices.size();
}

// plotting the polygon
void Polygon::plotPolygon(const string &filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << "\n";
        return;
    }

    for (const auto &v : vertices) {
        file << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    file << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n"; // Close the polygon
    file.close();

    string command = 
        "gnuplot -p -e \""
        "set terminal wxt; "
        "set xlabel 'X'; "
        "set ylabel 'Y'; "
        "set zlabel 'Z'; "
        "set view equal xyz; "
        "splot '" + filename + "' with linespoints pointtype 7 linecolor 'green'\"";

    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to execute GNUPLOT command.\n";
    }
}

// Translate the polygon
void Polygon::translate(double dx, double dy, double dz) {
    for (auto &v : vertices) {
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
    }
}

// for scaling the polygon
void Polygon::scale(double sx, double sy, double sz) {
    for (auto &v : vertices) {
        v[0] *= sx;
        v[1] *= sy;
        v[2] *= sz;
    }
}

// Rotate the polygon around a given axis
void Polygon::rotate(double angle, char axis) {
    double radians = angle * M_PI / 180.0;
    double cx, cy, cz;
    calculateCentroid(cx, cy, cz);

    for (auto &v : vertices) {
        double x = v[0] - cx, y = v[1] - cy, z = v[2] - cz;
        if (axis == 'x') {
            v[1] = cy + y * cos(radians) - z * sin(radians);
            v[2] = cz + y * sin(radians) + z * cos(radians);
        } else if (axis == 'y') {
            v[0] = cx + x * cos(radians) + z * sin(radians);
            v[2] = cz - x * sin(radians) + z * cos(radians);
        } else if (axis == 'z') {
            v[0] = cx + x * cos(radians) - y * sin(radians);
            v[1] = cy + x * sin(radians) + y * cos(radians);
        }
    }
}

void Polygon::saveToFile(const string &filename) const {
    ofstream file(filename, ios::app); // Open in append mode
    if (!file) {
        cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    cout << "Writing polygon vertices to file: " << filename << endl; // Debugging statement

    // Write polygon edges
    for (size_t i = 0; i < vertices.size(); i++) {
        size_t next = (i + 1) % vertices.size();
        file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << "\n";
        file << vertices[next][0] << " " << vertices[next][1] << " " << vertices[next][2] << "\n\n";
    }

    file.close();
    cout << "Finished writing polygon vertices to file." << endl; // Debugging statement
}
