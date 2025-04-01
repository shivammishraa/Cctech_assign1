#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <string>
#include "shape.h"

using namespace std;

class Bezier : public Shape {
private:
    vector<vector<double>> controlPoints;

public:
    Bezier();

    void plot(const string& filename) const override; // Override plot method
    void saveToFile(const string& filename) const override;

    void addControlPoint(double x, double y, double z);
    void translate(double dx, double dy, double dz);
    void rotate(double angle, char axis);
    void scale(double sx, double sy, double sz);

    // Additional methods
    vector<vector<double>> calculateBezierCurve(int numSegments) const;
    void plotBezier(const string& filename) const;
};

#endif // BEZIER_H
