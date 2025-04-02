#include "sphere.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

Sphere::Sphere(double r, int seg) : radius(r), segments(seg) {
    cout << "Generating sphere vertices..." << endl;

    // Generate vertices for the sphere
    for (int i = 0; i <= segments; i++) { // Latitude
        double theta = M_PI * i / segments; // From 0 to pi
        for (int j = 0; j <= segments; j++) { // Longitude
            double phi = 2 * M_PI * j / segments; // From 0 to 2*pi
            double x = radius * sin(theta) * cos(phi);
            double y = radius * sin(theta) * sin(phi);
            double z = radius * cos(theta);

            // Avoid invalid values
            if (isnan(x) || isnan(y) || isnan(z)) {
                cerr << "Error: Invalid vertex generated for sphere. Check radius and segments." << endl;
                return;
            }

            vertices.push_back({x, y, z});
        }
    }

    cout << "Generated " << vertices.size() << " vertices for the sphere." << endl;
}

void Sphere::plot(const string& filename) const { // Renamed from plotSphere to plot
    ofstream file(filename);
    for (auto& v : vertices) {
        file << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    file.close();

    ofstream gnuplotFile("plot_sphere.gnu");
    gnuplotFile << "set terminal wxt\n";
    gnuplotFile << "set parametric\n";
    gnuplotFile << "set hidden3d\n";
    gnuplotFile << "set mouse\n";
    gnuplotFile << "set urange [0:2*pi]\n";
    gnuplotFile << "set vrange [0:pi]\n";
    gnuplotFile << "set xlabel 'X'\n";
    gnuplotFile << "set ylabel 'Y'\n";
    gnuplotFile << "set zlabel 'Z'\n";
    gnuplotFile << "set view equal xyz\n";
    gnuplotFile << "r = " << radius << "\n";
    gnuplotFile << "splot '" << filename << "' with linespoints pointtype 7 linecolor 'blue'\n";
    gnuplotFile.close();
    system("gnuplot -p plot_sphere.gnu");
}

void Sphere::saveToFile(const string &filename) const {
    ofstream file(filename, ios::out); // Open in overwrite mode (ios::out)
    if (!file) {
        cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    int numLatitudes = segments + 1;
    int numLongitudes = segments + 1;

    // Write vertices along latitude lines
    for (int i = 0; i < numLatitudes; i++) {
        for (int j = 0; j < numLongitudes; j++) {
            int index = i * numLongitudes + j;
            file << vertices[index][0] << " " << vertices[index][1] << " " << vertices[index][2] << "\n";
        }
        file << "\n"; // Separate latitude lines
    }

    file.close();
}

void Sphere::translate(double dx, double dy, double dz) {
    for (auto& v : vertices) {
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
    }
}

void Sphere::scale(double factor) {
    for (auto& v : vertices) {
        v[0] *= factor;
        v[1] *= factor;
        v[2] *= factor;
    }
}
