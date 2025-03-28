#ifndef CUBOID_H
#define CUBOID_H

#include <vector>
#include <string>

using namespace std;

class Cuboid {
private:
    vector<vector<double>> vertices; // Stores cuboid vertices
public:
    Cuboid(double length, double width, double height);
    void plotCuboid(const string &filename);
    
    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, char axis);

    void saveToFile(const string &filename);
    void loadFromFile(const string &filename);

    
};

#endif // CUBOID_H
