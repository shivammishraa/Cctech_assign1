#include "scene.h"
#include <fstream>
#include <iostream>

using namespace std;

Scene::Scene() {}

void Scene::addCuboid(double x, double y, double z, double length, double width, double height) {
    shared_ptr<Cuboid> cuboid = make_shared<Cuboid>(length, width, height);
    cuboid->translate(x, y, z);
    shapes.push_back(cuboid);
    shapeTypes.push_back("cuboid");
}


void Scene::addCylinder(double x, double y, double z, double radius, double height, int segments) {
    shared_ptr<Cylinder> cylinder = make_shared<Cylinder>(radius, height, segments);
    cylinder->translate(x, y, z);
    shapes.push_back(cylinder);
    shapeTypes.push_back("cylinder");
}

void Scene::addSphere(double x, double y, double z, double radius, int segments) {
    shared_ptr<Sphere> sphere = make_shared<Sphere>(radius, segments);
    sphere->translate(x, y, z);
    shapes.push_back(sphere);
    shapeTypes.push_back("sphere");
}

void Scene::addTriangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
    shared_ptr<Triangle> triangle = make_shared<Triangle>(x1, y1, z1, x2, y2, z2, x3, y3, z3);
    shapes.push_back(triangle);
    shapeTypes.push_back("triangle");
}

void Scene::addPolygon(int sides, const vector<vector<double>>& vertices) {
    shared_ptr<Polygon> polygon = make_shared<Polygon>(sides);
    for (const auto& vertex : vertices) {
        polygon->addVertex(vertex[0], vertex[1], vertex[2]);
    }
    shapes.push_back(polygon);
    shapeTypes.push_back("polygon");
}

void Scene::addLine(double x1, double y1, double z1, double x2, double y2, double z2) {
    shared_ptr<Line3D> line = make_shared<Line3D>();
    line->setPoints(x1, y1, z1, x2, y2, z2);
    shapes.push_back(line);
    shapeTypes.push_back("line");
}

void Scene::addBezier(const vector<vector<double>>& controlPoints) {
    shared_ptr<Bezier> bezier = make_shared<Bezier>();
    for (const auto& point : controlPoints) {
        bezier->addControlPoint(point[0], point[1], point[2]);
    }
    shapes.push_back(bezier);
    shapeTypes.push_back("bezier");
}

void Scene::plotScene(const string& filename) const {
    // Clear the file initially
    ofstream clearFile(filename, ios::out);
    if (!clearFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    clearFile.close();

    // Append each shape to the file
    for (size_t i = 0; i < shapes.size(); ++i) {
        cout << "Saving shape " << shapeTypes[i] << " to file..." << endl;
        if (shapeTypes[i] == "cuboid") {
            static_pointer_cast<Cuboid>(shapes[i])->saveToFile(filename);
        } else if (shapeTypes[i] == "cylinder") {
            static_pointer_cast<Cylinder>(shapes[i])->saveToFile(filename);
        } else if (shapeTypes[i] == "sphere") {
            static_pointer_cast<Sphere>(shapes[i])->saveToFile(filename);
        } else if (shapeTypes[i] == "triangle") {
            static_pointer_cast<Triangle>(shapes[i])->saveToFile(filename);
        } else if (shapeTypes[i] == "polygon") {
            static_pointer_cast<Polygon>(shapes[i])->saveToFile(filename);
        } else if (shapeTypes[i] == "line") {
            static_pointer_cast<Line3D>(shapes[i])->saveToFile(filename);
        } else if (shapeTypes[i] == "bezier") {
            static_pointer_cast<Bezier>(shapes[i])->saveToFile(filename);
        }

        // Add a blank line to separate shapes
        ofstream file(filename, ios::app);
        if (file) {
            file << "\n\n"; // Ensure proper separation between shapes
            file.close();
        }
    }

    // Debugging: Print the contents of the file
    ifstream debugFile(filename);
    if (debugFile) {
        cout << "Contents of " << filename << ":\n";
        cout << debugFile.rdbuf(); // Print the file contents to the console
    }
    debugFile.close();

    // Plot the scene using GNUPLOT
    string command = 
        "gnuplot -p -e \""
        "set terminal wxt; "
        "set xlabel 'X'; "
        "set ylabel 'Y'; "
        "set zlabel 'Z'; "
        "set view equal xyz; "
        "splot '" + filename + "' with linespoints pointtype 7 linecolor 'black'\"";
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: Failed to execute GNUPLOT command." << endl;
    }
}
