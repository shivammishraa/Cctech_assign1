#include "../include/shapes.h"
#include <filesystem>

using namespace std;

// Ensure the dat_files directory exists
// void ensureDatFilesDirectory() {
//     string dir = "geometry/dat_files";
//     if (!filesystem::exists(dir)) {
//         filesystem::create_directories(dir);
//     }
// }

// Template class for Cuboid
template<typename T>
Cuboid<T>::Cuboid(Point<T, 3> origin, T length, T breadth, T height)
    : origin(origin), length(length), breadth(breadth), height(height) {}

    template<typename T>
void Cuboid<T>::generate() {
    ensureDatFilesDirectory();

    std::ofstream file("geometry/dat_files/cuboid.dat");
    if (!file) {
        std::cerr << "Error: Could not open cuboid.dat for writing." << std::endl;
        return;
    }

    T x = origin.coords[0];
    T y = origin.coords[1];
    T z = origin.coords[2];

    // Bottom face
    file << x << " " << y << " " << z << std::endl;
    file << x + length << " " << y << " " << z << std::endl;
    file << x + length << " " << y + breadth << " " << z << std::endl;
    file << x << " " << y + breadth << " " << z << std::endl;
    file << x << " " << y << " " << z << std::endl << std::endl;

    // Top face
    file << x << " " << y << " " << z + height << std::endl;
    file << x + length << " " << y << " " << z + height << std::endl;
    file << x + length << " " << y + breadth << " " << z + height << std::endl;
    file << x << " " << y + breadth << " " << z + height << std::endl;
    file << x << " " << y << " " << z + height << std::endl << std::endl;

    if (file.fail()) {
        std::cerr << "Error: Failed to write data to cuboid.dat." << std::endl;
    } else {
        std::cout << "Debug: Successfully wrote data to cuboid.dat." << std::endl;
    }

    file.close();

    // Debug: Confirm file contents
    std::ifstream debugFile("geometry/dat_files/cuboid.dat");
    if (debugFile) {
        std::cout << "Debug: Contents of cuboid.dat:" << std::endl;
        std::cout << debugFile.rdbuf() << std::endl;
    } else {
        std::cerr << "Error: cuboid.dat was not created successfully." << std::endl;
    }
}

template<typename T>
void Cuboid<T>::translate(T dx, T dy, T dz) {
    ensureDatFilesDirectory();

    std::ifstream fileIn("geometry/dat_files/cuboid.dat");
    std::ofstream fileOut("geometry/dat_files/cuboid_translated.dat");

    if (!fileIn || !fileOut) {
        std::cerr << "Error: Could not open cuboid files for reading/writing." << std::endl;
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
        std::cerr << "Error: Not enough points read from cuboid.dat!" << std::endl;
        return;
    }

    // **Write bottom face**
    for (int j = 0; j < 4; j++) {
        fileOut << (x[j] + dx) << " " << (y[j] + dy) << " " << (z[j] + dz) << std::endl;
    }
    fileOut << (x[0] + dx) << " " << (y[0] + dy) << " " << (z[0] + dz) << std::endl;  // Close loop
    fileOut << std::endl;

    // **Write top face**
    for (int j = 4; j < 8; j++) {
        fileOut << (x[j] + dx) << " " << (y[j] + dy) << " " << (z[j] + dz) << std::endl;
    }
    fileOut << (x[4] + dx) << " " << (y[4] + dy) << " " << (z[4] + dz) << std::endl;  // Close loop
    fileOut << std::endl;

    // **Write vertical edges**
    for (int j = 0; j < 4; j++) {
        fileOut << (x[j] + dx) << " " << (y[j] + dy) << " " << (z[j] + dz) << std::endl;
        fileOut << (x[j + 4] + dx) << " " << (y[j + 4] + dy) << " " << (z[j + 4] + dz) << std::endl;
        fileOut << std::endl;
    }

    if (fileOut.fail()) {
        std::cerr << "Error: Failed to write data to cuboid_translated.dat." << std::endl;
    } else {
        std::cout << "Debug: Successfully wrote data to cuboid_translated.dat." << std::endl;
    }

    fileIn.close();
    fileOut.close();
}
// Explicit template instantiation
template class Cuboid<double>;