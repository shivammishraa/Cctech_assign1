#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <string>

using namespace std;

class Sphere {
private:
    double radius;
    int segments;
    vector<vector<double>> vertices;

public:
    Sphere(double r, int seg);
    void plotSphere(const string& filename);
    void translate(double dx, double dy, double dz);
    void scale(double factor);

    // Add saveToFile method
    void saveToFile(const string& filename) const;
};

#endif
