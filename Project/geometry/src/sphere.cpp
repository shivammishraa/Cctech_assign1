#include "sphere.h"
#include <fstream>
#include <cmath>

using namespace std;

Sphere::Sphere(double r, int seg) : radius(r), segments(seg) {
    for (int i = 0; i <= segments; i++) {
        double theta = M_PI * i / segments;
        for (int j = 0; j < 2 * segments; j++) {
            double phi = 2 * M_PI * j / (2 * segments);
            double x = radius * sin(theta) * cos(phi);
            double y = radius * sin(theta) * sin(phi);
            double z = radius * cos(theta);
            vertices.push_back({x, y, z});
        }
    }
}

void Sphere::plotSphere(const string& filename) {
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
    gnuplotFile << "splot '" << filename << "' with points pointtype 7 linecolor 'blue'\n";
    gnuplotFile.close();

    system("gnuplot -p plot_sphere.gnu");
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
