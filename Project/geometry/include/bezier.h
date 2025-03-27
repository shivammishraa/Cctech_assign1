#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <string>

using namespace std;

class Bezier {
private:
    vector<vector<double>> controlPoints;

public:
    Bezier();
    void addControlPoint(double x, double y, double z);
    void plotBezier(const string& filename);
    void translate(double dx, double dy, double dz); // Using Eigen
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);
    vector<vector<double>> calculateBezierCurve(int numSegments);
};

#endif
