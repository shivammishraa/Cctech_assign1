#include "../include/shapes.h"
#include <filesystem>

using namespace std;

// Template class for Cuboid
template<typename T>
Cuboid<T>::Cuboid(Point<T, 3> origin, T length, T breadth, T height)
    : origin(origin), length(length), breadth(breadth), height(height) {}

template<typename T>
void Cuboid<T>::generate() {
    ofstream file("geometry/dat_files/cuboid.dat");
    if (!file) {
        cerr << "Error opening file" << endl;
        return;
    }

    T x = origin.coords[0];
    T y = origin.coords[1];
    T z = origin.coords[2];

    // Bottom face
    file << x << " " << y << " " << z << endl;
    file << x + length << " " << y << " " << z << endl;
    file << x + length << " " << y + breadth << " " << z << endl;
    file << x << " " << y + breadth << " " << z << endl;
    file << x << " " << y << " " << z << endl << endl;

    // Top face
    file << x << " " << y << " " << z + height << endl;
    file << x + length << " " << y << " " << z + height << endl;
    file << x + length << " " << y + breadth << " " << z + height << endl;
    file << x << " " << y + breadth << " " << z + height << endl;
    file << x << " " << y << " " << z + height << endl << endl;

    file.close();
}

// Function to translate a cuboid
template<typename T>
void Cuboid<T>::translate(T dx, T dy, T dz) {
    ifstream fileIn("geometry/dat_files/cuboid.dat");
    ofstream fileOut("geometry/dat_files/cuboid_translated.dat");

    if (!fileIn || !fileOut) {
        cerr << "Error opening cuboid files" << endl;
        return;
    }

    T x[8], y[8], z[8];
    int i = 0;

    // Read exactly 8 points
    while (fileIn >> x[i] >> y[i] >> z[i]) {
        i++;
        if (i == 8) break;
    }

    if (i < 8) {
        cerr << "Error: Not enough points read from cuboid.dat!" << endl;
        return;
    }

    // **Write bottom face**
    for (int j = 0; j < 4; j++) {
        fileOut << (x[j] + dx) << " " << (y[j] + dy) << " " << (z[j] + dz) << endl;
    }
    fileOut << (x[0] + dx) << " " << (y[0] + dy) << " " << (z[0] + dz) << endl;  // Close loop
    fileOut << endl;

    // **Write top face**
    for (int j = 4; j < 8; j++) {
        fileOut << (x[j] + dx) << " " << (y[j] + dy) << " " << (z[j] + dz) << endl;
    }
    fileOut << (x[4] + dx) << " " << (y[4] + dy) << " " << (z[4] + dz) << endl;  // Close loop
    fileOut << endl;

    // **Write vertical edges**
    for (int j = 0; j < 4; j++) {
        fileOut << (x[j] + dx) << " " << (y[j] + dy) << " " << (z[j] + dz) << endl;
        fileOut << (x[j + 4] + dx) << " " << (y[j + 4] + dy) << " " << (z[j + 4] + dz) << endl;
        fileOut << endl;
    }

    fileIn.close();
    fileOut.close();
    cout << "Debug: Translated cuboid written to cuboid_translated.dat!" << endl;
}




// Explicit template instantiation
template class Cuboid<double>;
