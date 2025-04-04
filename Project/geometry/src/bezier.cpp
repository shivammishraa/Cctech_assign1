#include "../include/bezier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

class TransformationMatrix {
private:
    double matrix[4][4]; // 4x4 transformation matrix

public:
    TransformationMatrix() {
        // Initialize as identity matrix
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = (i == j) ? 1 : 0;
            }
        }
    }

    void setTranslation(double dx, double dy, double dz) {
        matrix[0][3] = dx;
        matrix[1][3] = dy;
        matrix[2][3] = dz;
    }

    vector<double> apply(const vector<double>& point) {
        vector<double> result(3, 0);
        double x = point[0], y = point[1], z = point[2];

        result[0] = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
        result[1] = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
        result[2] = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3];

        return result;
    }
};

int binomialCoeff(int n, int k) {
    if (k < 0 || k > n) {
        throw invalid_argument("Invalid values for n and k in binomialCoeff");
    }

    int res = 1;
    if (k > n - k) {
        k = n - k; // C(n, k) == C(n, n-k)
    }

    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

Bezier::Bezier() {
    controlPoints = {};
}

void Bezier::addControlPoint(double x, double y, double z) {
    controlPoints.push_back({x, y, z});
}

vector<vector<double>> Bezier::calculateBezierCurve(int numSegments) const {
    vector<vector<double>> curve;
    int n = controlPoints.size() - 1;

    for (int i = 0; i <= numSegments; i++) {
        double t = (double)i / numSegments;
        vector<double> point = {0, 0, 0};

        for (int j = 0; j <= n; j++) {
            double bernstein = binomialCoeff(n, j) * pow(t, j) * pow(1 - t, n - j);
            point[0] += bernstein * controlPoints[j][0];
            point[1] += bernstein * controlPoints[j][1];
            point[2] += bernstein * controlPoints[j][2];
        }
        curve.push_back(point);
    }
    return curve;
}

void Bezier::plotBezier(const string& filename) const {
    vector<vector<double>> curve = calculateBezierCurve(100);
    ofstream file(filename);

    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (const auto& point : curve) {
        file << point[0] << " " << point[1] << " " << point[2] << "\n";
    }
    file.close();

    string command = 
        "gnuplot -p -e \""
        "set terminal wxt; "
        "set xlabel 'X'; "
        "set ylabel 'Y'; "
        "set zlabel 'Z'; "
        "set view equal xyz; "
        "splot '" + filename + "' with lines linewidth 2 linecolor 'blue'\"";
    system(command.c_str());
}

void Bezier::translate(double dx, double dy, double dz) {
    TransformationMatrix transformation;
    transformation.setTranslation(dx, dy, dz);

    for (auto& point : controlPoints) {
        point = transformation.apply(point);
    }
}

void Bezier::rotate(double angle, char axis) {
    double radians = angle * M_PI / 180.0;
    for (auto& point : controlPoints) {
        double x = point[0], y = point[1], z = point[2];
        if (axis == 'x') {
            point[1] = y * cos(radians) - z * sin(radians);
            point[2] = y * sin(radians) + z * cos(radians);
        } else if (axis == 'y') {
            point[0] = x * cos(radians) + z * sin(radians);
            point[2] = -x * sin(radians) + z * cos(radians);
        } else if (axis == 'z') {
            point[0] = x * cos(radians) - y * sin(radians);
            point[1] = x * sin(radians) + y * cos(radians);
        }
    }
}

void Bezier::scale(double sx, double sy, double sz) {
    for (auto& point : controlPoints) {
        point[0] *= sx;
        point[1] *= sy;
        point[2] *= sz;
    }
}

void Bezier::saveToFile(const string &filename) const {
    ofstream file(filename, ios::app); // Open in append mode
    if (!file) {
        cerr << "Error: Cannot open file for writing.\n";
        return;
    }

    for (size_t i = 0; i < controlPoints.size() - 1; i++) {
        file << controlPoints[i][0] << " " << controlPoints[i][1] << " " << controlPoints[i][2] << "\n";
        file << controlPoints[i + 1][0] << " " << controlPoints[i + 1][1] << " " << controlPoints[i + 1][2] << "\n\n";
    }

    file.close();
}

void Bezier::plot(const std::string& filename) const {
    plotBezier(filename); // Use the existing plotBezier method
}