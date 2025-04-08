#include "stl_shape.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor to parse the STL file
STLShape::STLShape(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error: Could not open STL file: " << filepath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("vertex") != string::npos) {
            istringstream iss(line);
            string temp;
            double x, y, z;
            iss >> temp >> x >> y >> z; // Parse the vertex line
            vertices.push_back({x, y, z});
        }
    }

    file.close();
}

// Save vertices to a .dat file
void STLShape::saveToFile(const string& filename) const {
    ofstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Error: Could not open .dat file: " << filename << endl;
        return;
    }

    for (size_t i = 0; i < vertices.size(); i += 3) {
        if (i + 2 < vertices.size()) {
            file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << endl;
            file << vertices[i + 1][0] << " " << vertices[i + 1][1] << " " << vertices[i + 1][2] << endl;
            file << vertices[i + 2][0] << " " << vertices[i + 2][1] << " " << vertices[i + 2][2] << endl;

            file << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << endl;

            file << endl; // Separate triangles
        }
        file << endl; // Separate triangles
    }

    file.close();
}

// Plot the shape using GNUPLOT
void STLShape::plot(const string& filename) const {
    saveToFile(filename);

    string command = 
        "gnuplot -p -e \""
        "set terminal wxt; "
        "set xlabel 'X'; "
        "set ylabel 'Y'; "
        "set zlabel 'Z'; "
        "set view equal xyz; "
        "splot '" + filename + "' with lines pointtype 7 linecolor 'blue'\"";
    system(command.c_str());
}