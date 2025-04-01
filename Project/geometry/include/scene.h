#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>
#include "cuboid.h"
#include "cylinder.h"
#include "sphere.h"
#include "triangle.h"
#include "polygon.h"
#include "line3D.h"
#include "bezier.h"

class Scene {
private:
    std::vector<std::shared_ptr<void>> shapes; // Store shapes as shared pointers
    std::vector<std::string> shapeTypes;      // Store shape types for identification

public:
    Scene();

    void addCuboid(double x, double y, double z, double length, double width, double height);
    void addCylinder(double x, double y, double z, double radius, double height, int segments);
    void addSphere(double x, double y, double z, double radius, int segments);
    void addTriangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
    void addPolygon(int sides, const std::vector<std::vector<double>>& vertices);
    void addLine(double x1, double y1, double z1, double x2, double y2, double z2);
    void addBezier(const std::vector<std::vector<double>>& controlPoints);
    void plotScene(const std::string& filename) const; 
};

#endif // SCENE_H
