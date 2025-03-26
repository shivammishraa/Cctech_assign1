#include "../include/sphere.h"
#include <filesystem>

template <class T>
void Sphere<T>::generateSphere() {
    points.clear(); // Clear any existing points

    double latStep = M_PI / latSegments; // Step size for latitude
    double lonStep = 2 * M_PI / lonSegments; // Step size for longitude

    for (int i = 0; i <= latSegments; ++i) {
        double theta = i * latStep; // Latitude angle
        for (int j = 0; j <= lonSegments; ++j) {
            double phi = j * lonStep; // Longitude angle

            T x = center.x() + radius * sin(theta) * cos(phi);
            T y = center.y() + radius * sin(theta) * sin(phi);
            T z = center.z() + radius * cos(theta);

            points.emplace_back(Point<T, 3>({x, y, z}));
        }
    }
}

template <class T>
void Sphere<T>::translate(T dx, T dy, T dz) {
    center.x() += dx;
    center.y() += dy;
    center.z() += dz;

    for (auto& point : points) {
        point.x() += dx;
        point.y() += dy;
        point.z() += dz;
    }
}

template <class T>
void Sphere<T>::scale(T factor) {
    radius *= factor;

    for (auto& point : points) {
        point.x() = center.x() + (point.x() - center.x()) * factor;
        point.y() = center.y() + (point.y() - center.y()) * factor;
        point.z() = center.z() + (point.z() - center.z()) * factor;
    }
}

template <class T>
void Sphere<T>::writeToFile(const std::string& filename) const {
    std::filesystem::create_directories("../../geometry/dat_files");

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing sphere data." << std::endl;
        return;
    }

    for (const auto& point : points) {
        file << point.x() << " " << point.y() << " " << point.z() << "\n";
    }

    file.close();
}

// Explicit template instantiation
template class Sphere<double>;
template class Sphere<float>;
template class Sphere<int>;