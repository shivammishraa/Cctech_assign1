#ifndef LINE3D_H
#define LINE3D_H

#include <vector>
#include <string>
#include "shape.h"

class Line3D : public Shape {
private:
    std::vector<std::vector<double>> points;

public:
    Line3D();

    void plot(const std::string& filename) const override; // Override plot method
    void saveToFile(const std::string& filename) const override;

    void setPoints(double x1, double y1, double z1, double x2, double y2, double z2);
    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);

    // Additional method
    void plotLine(const std::string& filename) const; // Specific plot method
};

#endif // LINE3D_H
