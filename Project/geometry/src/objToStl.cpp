#include "objToStl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

// Hash function for vector<double> representing a 3D point
struct VectorHash {
    size_t operator()(const vector<double>& v) const {
        hash<double> hasher;
        return ((hasher(v[0]) ^ (hasher(v[1]) << 1)) >> 1) ^ (hasher(v[2]) << 1);
    }
};

// Equality comparator for 3D points
struct VectorEqual {
    bool operator()(const vector<double>& a, const vector<double>& b) const {
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }
};

// Convert OBJ to STL and plot using GNUPLOT
void ObjToStlConverter::convertAndPlot(const string &objFilename, const string &stlFilename) {
    if (!ObjToStlConverter::convert(objFilename, stlFilename)) {
        cerr << "Error: Conversion failed. Cannot plot.\n";
        return;
    }

    STLShape shape(stlFilename);
}

// Convert OBJ to STL
bool ObjToStlConverter::convert(const string &objFilename, const string &stlFilename) {

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    auto [vertices, faces] = ObjToStlConverter::readObj(objFilename);

    if (vertices.empty()) {
        cerr << "Error: Failed to read OBJ file or file is empty.\n";
        return false;
    }

    ObjToStlConverter::writeStl(vertices, faces, stlFilename);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Converted " << objFilename << " to " << stlFilename << " in " << duration << " ms\n";

    return true;
}

// Read OBJ file and extract unique vertices and mapped face indices
pair<vector<vector<double>>, vector<vector<int>>> ObjToStlConverter::readObj(const string &filename) {
    ifstream file(filename);
    vector<vector<double>> dedupedVertices;
    vector<vector<int>> faces;

    unordered_map<vector<double>, int, VectorHash, VectorEqual> vertexMap;

    if (!file.is_open()) {
        cerr << "Error: Could not open OBJ file: " << filename << "\n";
        return {dedupedVertices, faces};
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string prefix;
        iss >> prefix;

        if (prefix == "v") {
            double x, y, z;
            if (!(iss >> x >> y >> z))
                continue;

            vector<double> vertex = {x, y, z};
            if (vertexMap.find(vertex) == vertexMap.end()) {
                vertexMap[vertex] = static_cast<int>(dedupedVertices.size());
                dedupedVertices.push_back(vertex);
            }
        } else if (prefix == "f") {
            vector<int> face;
            string token;
            while (iss >> token) {
                try {
                    int index = stoi(token) - 1;
                    face.push_back(index);
                } catch (const exception &) {
                    continue;
                }
            }
            if (face.size() >= 3)
                faces.push_back(face);
        }
    }

    file.close();
    // cout << "Unique vertices: " << dedupedVertices.size() << "\n";
    // cout << "Faces: " << faces.size() << "\n";
    return {dedupedVertices, faces};
}

// Write STL file
void ObjToStlConverter::writeStl(const vector<vector<double>> &vertices,
                                 const vector<vector<int>> &faces,
                                 const string &filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not write to STL file: " << filename << "\n";
        return;
    }

    outFile << "solid obj_to_stl\n";

    for (const auto &face : faces) {
        // Triangulate polygons with >3 vertices
        for (size_t i = 1; i + 1 < face.size(); ++i) {
            outFile << "  facet normal 0 0 0\n";
            outFile << "    outer loop\n";

            const auto &v0 = vertices[face[0]];
            const auto &v1 = vertices[face[i]];
            const auto &v2 = vertices[face[i + 1]];

            outFile << "      vertex " << v0[0] << " " << v0[1] << " " << v0[2] << "\n";
            outFile << "      vertex " << v1[0] << " " << v1[1] << " " << v1[2] << "\n";
            outFile << "      vertex " << v2[0] << " " << v2[1] << " " << v2[2] << "\n";

            outFile << "    endloop\n";
            outFile << "  endfacet\n";
        }
    }

    outFile << "endsolid obj_to_stl\n";
    outFile.close();
}
