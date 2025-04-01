#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <string>
#include "shape.h"

class Triangle : public Shape {
private:
    std::vector<std::vector<double>> vertices;

public:
    Triangle(double x1, double y1, double z1,
             double x2, double y2, double z2,
             double x3, double y3, double z3);

    void plot(const std::string& filename) const override; // Override plot method
    void saveToFile(const std::string& filename) const override;

    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis, double Px, double Py, double Pz);

    // Additional method
    void plotTriangle(const std::string& filename) const; // Specific plot method marked as const
};

#endif // TRIANGLE_H
