#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include <filesystem>

template<typename T, size_t N>
class Point {
public:
    std::array<T, N> coords;

    // Default constructor
    Point() {
        coords.fill(0);
    }

    // Constructor with initializer list
    Point(std::initializer_list<T> values) {
        size_t i = 0;
        for (T value : values) {
            if (i < N) coords[i++] = value;
        }
    }

    // Accessors for x, y, z (conditionally for 3D points)
    T& x() { return coords[0]; }
    const T& x() const { return coords[0]; }

    T& y() { static_assert(N >= 2, "Point must have at least 2 dimensions"); return coords[1]; }
    const T& y() const { static_assert(N >= 2, "Point must have at least 2 dimensions"); return coords[1]; }

    // z() is only available for 3D points
    template <size_t M = N>
    typename std::enable_if<M >= 3, T&>::type z() { return coords[2]; }

    template <size_t M = N>
    typename std::enable_if<M >= 3, const T&>::type z() const { return coords[2]; }

    // Input method
    void input() {
        for (size_t i = 0; i < N; ++i) {
            std::cin >> coords[i];
        }
    }
};

template<typename T, size_t N>
class DataFile {
public:
    void generate(const Point<T, N>& p1, const Point<T, N>& p2) {
        std::ofstream file("geometry/dat_files/points.dat");
        if (!file) {
            std::cerr << "Error opening file" << std::endl;
            return;
        }

        int totalpoints = 10;
        std::array<T, N> step;
        for (size_t i = 0; i < N; i++) {
            step[i] = (p2.coords[i] - p1.coords[i]) / static_cast<double>(totalpoints - 1);
        }

        for (int i = 0; i < totalpoints; i++) {
            for (size_t j = 0; j < N; j++) {
                file << (p1.coords[j] + i * step[j]) << " ";
            }
            file << std::endl;
        }
        file.close();
    }

    void generatePolyline(int numPoints) {
        std::ofstream file("geometry/dat_files/points.dat");
        if (!file) {
            std::cerr << "Error opening file" << std::endl;
            return;
        }

        Point<T, N> points[numPoints];
        std::cout << "Enter " << numPoints << " points (x y for 2D, x y z for 3D):\n";

        for (int i = 0; i < numPoints; i++) {
            std::cout << "Point " << i + 1 << ": ";
            points[i].input();
        }

        for (int i = 0; i < numPoints; i++) {
            for (size_t j = 0; j < N; j++) {
                file << points[i].coords[j] << " ";
            }
            file << std::endl;
        }

        file.close();
    }

    void translatePolyline(int numPoints, const std::array<T, N>& displacement) {
        std::ifstream fileIn("geometry/dat_files/points.dat");
        std::ofstream fileOut("geometry/dat_files/points_translated.dat");

        if (!fileIn || !fileOut) {
            std::cerr << "Error opening files" << std::endl;
            return;
        }

        Point<T, N> point;
        for (int i = 0; i < numPoints; i++) {
            for (size_t j = 0; j < N; j++) {
                fileIn >> point.coords[j];
                point.coords[j] += displacement[j];
                fileOut << point.coords[j] << " ";
            }
            fileOut << std::endl;
        }

        fileIn.close();
        fileOut.close();
    }
};

template<typename T, size_t N>
class GnuPlotting {
public:
    void plot();
    void plotTranslated();
};

// Function declarations for cuboid operations
void translateCuboid(double dx, double dy, double dz);
void plotCuboid();
void plotTranslatedCuboid();

#endif // LOGIC_H