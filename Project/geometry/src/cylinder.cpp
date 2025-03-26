#include "../include/cylinder.h"
#include <cmath>
#include <filesystem>

template <class T>
void Cylinder<T>::generateCylinder() {
    double angleStep = 2 * M_PI / segments;

    // Ensure the dat_files directory exists
    std::filesystem::create_directories("../../geometry/dat_files");

    // Resize the baseCircle and topCircle vectors to match the number of segments
    baseCircle.resize(segments);
    topCircle.resize(segments);

    // Open the file to write cylinder data
    std::ofstream file("../../geometry/dat_files/cylinder.dat");
    if (!file) {
        std::cerr << "Error: Could not open file for writing cylinder data." << std::endl;
        return;
    }

    for (int i = 0; i < segments; ++i) {
        double angle = i * angleStep;

        T x = center.x() + radius * cos(angle);
        T y = center.y() + radius * sin(angle);

        baseCircle[i] = Point<T, 3>({x, y, center.z()});
        topCircle[i] = Point<T, 3>({x, y, center.z() + height});

        // Write the base and top circle points to the file
        file << baseCircle[i].x() << " " << baseCircle[i].y() << " " << baseCircle[i].z() << "\n";
        file << topCircle[i].x() << " " << topCircle[i].y() << " " << topCircle[i].z() << "\n\n";
    }

    // Close the file
    file.close();
}

template <class T>
void Cylinder<T>::translate(T dx, T dy, T dz) {
    // Update the center of the cylinder
    center.x() += dx;
    center.y() += dy;
    center.z() += dz;

    // Update the base and top circle points
    for (int i = 0; i < segments; ++i) {
        baseCircle[i].x() += dx;
        baseCircle[i].y() += dy;
        baseCircle[i].z() += dz;

        topCircle[i].x() += dx;
        topCircle[i].y() += dy;
        topCircle[i].z() += dz;
    }

    // Write the translated cylinder data to a file
    std::ofstream file("../../geometry/dat_files/cylinder_translated.dat");
    if (!file) {
        std::cerr << "Error: Could not open file for writing translated cylinder data." << std::endl;
        return;
    }

    for (int i = 0; i < segments; ++i) {
        file << baseCircle[i].x() << " " << baseCircle[i].y() << " " << baseCircle[i].z() << "\n";
        file << topCircle[i].x() << " " << topCircle[i].y() << " " << topCircle[i].z() << "\n\n";
    }

    file.close();
}


template <class T>
void Cylinder<T>::rotate(T angleDeg, char axis) {
    double angleRad = angleDeg * M_PI / 180.0;

    for (int i = 0; i < segments; ++i) {
        if (axis == 'x' || axis == 'X') {
            // Rotate around X-axis
            T yNewBase = center.y() + (baseCircle[i].y() - center.y()) * cos(angleRad) -
                         (baseCircle[i].z() - center.z()) * sin(angleRad);
            T zNewBase = center.z() + (baseCircle[i].y() - center.y()) * sin(angleRad) +
                         (baseCircle[i].z() - center.z()) * cos(angleRad);

            T yNewTop = center.y() + (topCircle[i].y() - center.y()) * cos(angleRad) -
                        (topCircle[i].z() - center.z()) * sin(angleRad);
            T zNewTop = center.z() + (topCircle[i].y() - center.y()) * sin(angleRad) +
                        (topCircle[i].z() - center.z()) * cos(angleRad);

            baseCircle[i].y() = yNewBase;
            baseCircle[i].z() = zNewBase;

            topCircle[i].y() = yNewTop;
            topCircle[i].z() = zNewTop;
        } else if (axis == 'y' || axis == 'Y') {
            // Rotate around Y-axis
            T xNewBase = center.x() + (baseCircle[i].x() - center.x()) * cos(angleRad) +
                         (baseCircle[i].z() - center.z()) * sin(angleRad);
            T zNewBase = center.z() - (baseCircle[i].x() - center.x()) * sin(angleRad) +
                         (baseCircle[i].z() - center.z()) * cos(angleRad);

            T xNewTop = center.x() + (topCircle[i].x() - center.x()) * cos(angleRad) +
                        (topCircle[i].z() - center.z()) * sin(angleRad);
            T zNewTop = center.z() - (topCircle[i].x() - center.x()) * sin(angleRad) +
                        (topCircle[i].z() - center.z()) * cos(angleRad);

            baseCircle[i].x() = xNewBase;
            baseCircle[i].z() = zNewBase;

            topCircle[i].x() = xNewTop;
            topCircle[i].z() = zNewTop;
        } else if (axis == 'z' || axis == 'Z') {
            // Rotate around Z-axis
            T xNewBase = center.x() + (baseCircle[i].x() - center.x()) * cos(angleRad) -
                         (baseCircle[i].y() - center.y()) * sin(angleRad);
            T yNewBase = center.y() + (baseCircle[i].x() - center.x()) * sin(angleRad) +
                         (baseCircle[i].y() - center.y()) * cos(angleRad);

            T xNewTop = center.x() + (topCircle[i].x() - center.x()) * cos(angleRad) -
                        (topCircle[i].y() - center.y()) * sin(angleRad);
            T yNewTop = center.y() + (topCircle[i].x() - center.x()) * sin(angleRad) +
                        (topCircle[i].y() - center.y()) * cos(angleRad);

            baseCircle[i].x() = xNewBase;
            baseCircle[i].y() = yNewBase;

            topCircle[i].x() = xNewTop;
            topCircle[i].y() = yNewTop;
        }
    }

    // Write the rotated cylinder data to a file
    std::ofstream file("../../geometry/dat_files/cylinder_rotated.dat");
    if (!file) {
        std::cerr << "Error: Could not open file for writing rotated cylinder data." << std::endl;
        return;
    }

    for (int i = 0; i < segments; ++i) {
        file << baseCircle[i].x() << " " << baseCircle[i].y() << " " << baseCircle[i].z() << "\n";
        file << topCircle[i].x() << " " << topCircle[i].y() << " " << topCircle[i].z() << "\n\n";
    }

    file.close();
}

template <class T>
void Cylinder<T>::scale(T factor) {
    radius *= factor;
    height *= factor;

    for (int i = 0; i < segments; ++i) {
        baseCircle[i].x() = center.x() + (baseCircle[i].x() - center.x()) * factor;
        baseCircle[i].y() = center.y() + (baseCircle[i].y() - center.y()) * factor;
        baseCircle[i].z() = center.z() + (baseCircle[i].z() - center.z()) * factor;

        topCircle[i].x() = center.x() + (topCircle[i].x() - center.x()) * factor;
        topCircle[i].y() = center.y() + (topCircle[i].y() - center.y()) * factor;
        topCircle[i].z() = center.z() + (topCircle[i].z() - center.z()) * factor;
    }

    // Write the scaled cylinder data to a file
    std::ofstream file("../../geometry/dat_files/cylinder_scaled.dat");
    if (!file) {
        std::cerr << "Error: Could not open file for writing scaled cylinder data." << std::endl;
        return;
    }

    for (int i = 0; i < segments; ++i) {
        file << baseCircle[i].x() << " " << baseCircle[i].y() << " " << baseCircle[i].z() << "\n";
        file << topCircle[i].x() << " " << topCircle[i].y() << " " << topCircle[i].z() << "\n\n";
    }

    file.close();
}

// Explicit template instantiation
template class Cylinder<double>;
template class Cylinder<float>;
template class Cylinder<int>;