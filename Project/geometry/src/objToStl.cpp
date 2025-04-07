#include "objToStl.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Convert OBJ to STL and plot using GNUPLOT
void ObjToStlConverter::convertAndPlot(const string &objFilename, const string &stlFilename)
{
    if (!ObjToStlConverter::convert(objFilename, stlFilename))
    { // Static function call
        cerr << "Error: Conversion failed. Cannot plot.\n";
        return;
    }

    // Convert STL to DAT for GNUPLOT
    STLShape shape(stlFilename);

    string outputDataFile = "assets/" + stlFilename.substr(0, stlFilename.rfind(".")) + ".dat";
    shape.plot(outputDataFile);
}

// Convert OBJ to STL
bool ObjToStlConverter::convert(const string &objFilename, const string &stlFilename)
{
    auto [vertices, faces] = ObjToStlConverter::readObj(objFilename); //  Static function call

    if (vertices.empty())
    {
        cerr << "Error: Failed to read OBJ file or file is empty.\n";
        return false;
    }

    ObjToStlConverter::writeStl(vertices, faces, stlFilename); //  Static function call
    cout << "Converted " << objFilename << " to " << stlFilename << "\n";

    return true;
}

// Read OBJ file and extract vertices and faces
pair<vector<vector<double>>, vector<vector<int>>> ObjToStlConverter::readObj(const string &filename)
{
    ifstream file(filename);
    vector<vector<double>> vertices;
    vector<vector<int>> faces;

    if (!file.is_open())
    {
        cerr << "Error: Could not open OBJ file: " << filename << "\n";
        return {vertices, faces};
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string prefix;
        iss >> prefix;

        if (prefix == "v")
        { // Vertex line
            double x, y, z;
            if (!(iss >> x >> y >> z))
                continue;
            vertices.push_back({x, y, z});
        }
        else if (prefix == "f")
        { // Face line
            vector<int> face;
            string vertexStr;
            while (iss >> vertexStr)
            {
                try
                {
                    int vertexIndex = stoi(vertexStr) - 1;
                    if (vertexIndex < 0 || vertexIndex >= static_cast<int>(vertices.size()))
                        continue;
                    face.push_back(vertexIndex);
                }
                catch (const invalid_argument &)
                {
                    cerr << "Warning: Invalid vertex index in face: " << vertexStr << "\n";
                }
            }
            if (face.size() >= 3)
            {
                faces.push_back(face);
            }
        }
    }

    file.close();
    return {vertices, faces};
}

// Write STL file
void ObjToStlConverter::writeStl(const vector<vector<double>> &vertices,
                                 const vector<vector<int>> &faces,
                                 const string &filename)
{
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not write to STL file: " << filename << "\n";
        return;
    }

    outFile << "solid obj_to_stl\n";
    for (const auto &face : faces)
    {
        if (face.size() < 3)
            continue;

        outFile << "  facet normal 0 0 0\n";
        outFile << "    outer loop\n";

        for (int i = 0; i < 3; ++i)
        {
            const auto &v = vertices[face[i]];
            outFile << "      vertex " << v[0] << " " << v[1] << " " << v[2] << "\n";
        }

        outFile << "    endloop\n";
        outFile << "  endfacet\n";
    }
    outFile << "endsolid obj_to_stl\n";

    outFile.close();
}
