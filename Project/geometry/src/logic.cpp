#include "../include/logic.h"
#include<sstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void ensureDatFilesDirectory() {
    string dir = "geometry/dat_files";
    if (!fs::exists(dir)) {
        fs::create_directories(dir);
    }
}

// Template class for Points
template<typename T, size_t N>
Point<T, N>::Point() {
    coords.fill(0);
}

template<typename T, size_t N>
void Point<T, N>::input() {
    for (size_t i = 0; i < N; i++) {
        cin >> coords[i];
    }
}

// Template class for DataFile
template<typename T, size_t N>
void DataFile<T, N>::generate(const Point<T, N>& p1, const Point<T, N>& p2) {
    ensureDatFilesDirectory();
    ofstream file("geometry/dat_files/points.dat");
    if (!file) {
        cerr << "Error opening file" << endl;
        return;
    }

    int totalpoints = 10;
    array<T, N> step;
    for (size_t i = 0; i < N; i++) {
        step[i] = (p2.coords[i] - p1.coords[i]) / static_cast<double>(totalpoints - 1);
    }

    for (int i = 0; i < totalpoints; i++) {
        for (size_t j = 0; j < N; j++) {
            file << (p1.coords[j] + i * step[j]) << " ";
        }
        file << endl;
    }
    file.close();
}

// Template class for Polyline
template<typename T, size_t N>
void DataFile<T, N>::generatePolyline(int numPoints) {
    ensureDatFilesDirectory();
    ofstream file("geometry/dat_files/points.dat");  // Ensure correct filename
    if (!file) {
        cerr << "Error opening file" << endl;
        return;
    }

    Point<T, N> points[numPoints];  // Store user points
    cout << "Enter " << numPoints << " points (x y for 2D, x y z for 3D):\n";

    for (int i = 0; i < numPoints; i++) {
        cout << "Point " << i + 1 << ": ";
        points[i].input();  // Read user input

        // Debugging each point input
        cout << "Debug: Stored Point " << i + 1 << ": ";
        for (size_t j = 0; j < N; j++) {
            cout << points[i].coords[j] << " ";
        }
        cout << endl;
    }

    // Write to `points.dat`
    for (int i = 0; i < numPoints; i++) {
        for (size_t j = 0; j < N; j++) {
            file << points[i].coords[j] << " ";  
        }
        file << endl;
    }

    file.close();
    cout << "Debug: Polyline data saved in points.dat!\n";
}

// Function to translate polyline
template<typename T, size_t N>
void DataFile<T, N>::translatePolyline(int numPoints, const array<T, N>& displacement) {
    ensureDatFilesDirectory();
    ifstream fileIn("geometry/dat_files/points.dat");  
    ofstream fileOut("geometry/dat_files/points_translated.dat");  

    if (!fileIn) {
        cerr << "Error: Cannot open points.dat for reading!" << endl;
        return;
    }
    if (!fileOut) {
        cerr << "Error: Cannot open points_translated.dat for writing!" << endl;
        return;
    }

    cout << "Debug: Translating polyline by ";
    for (size_t j = 0; j < N; j++) {
        cout << displacement[j] << " ";
    }
    cout << endl;

    Point<T, N> point;
    for (int i = 0; i < numPoints; i++) {
        for (size_t j = 0; j < N; j++) {
            fileIn >> point.coords[j];  // Read original point
        }

        cout << "Original Point " << i + 1 << ": ";
        for (size_t j = 0; j < N; j++) {
            cout << point.coords[j] << " ";
            point.coords[j] += displacement[j];  // Apply translation
        }
        cout << " -> Translated: ";
        for (size_t j = 0; j < N; j++) {
            cout << point.coords[j] << " ";
            fileOut << point.coords[j] << " ";  // Write translated point
        }
        cout << endl;
        fileOut << endl;
    }

    fileIn.close();
    fileOut.close();
    cout << "Debug: Translation completed, check points_translated.dat!" << endl;
}

// Function to translate a cuboid
void translateCuboid(double dx, double dy, double dz) {
    ensureDatFilesDirectory();
    ifstream fileIn("geometry/dat_files/cuboid.dat");
    ofstream fileOut("geometry/dat_files/cuboid_translated.dat");

    if (!fileIn || !fileOut) {
        cerr << "Error opening cuboid files" << endl;
        return;
    }

    string line;
    while (getline(fileIn, line)) {
        if (line.empty()) { 
            // Preserve empty lines to maintain correct formatting
            fileOut << endl;
            continue;
        }

        istringstream iss(line);//This takes a single line from the file and allows us to extract numbers (x, y, z) from it.
        double x, y, z;
        if (iss >> x >> y >> z) { //This extracts three double values from the line.
            // Apply translation
            fileOut << (x + dx) << " " << (y + dy) << " " << (z + dz) << endl;
        }
    }

    fileIn.close();
    fileOut.close();
    cout << "Debug: Translated cuboid written to cuboid_translated.dat!" << endl;
}



// Template class for GnuPlotting
template<typename T, size_t N>
void GnuPlotting<T, N>::plotTranslated() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Translated Line Plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'x-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'y-axis'\n");

    if (N == 3) {
        fprintf(gnuplotPipe, "set zlabel 'z-axis'\n");
        fprintf(gnuplotPipe, "splot 'geometry/dat_files/points_translated.dat' with linespoints lw 2 lc rgb 'green'\n");
    } else {
        fprintf(gnuplotPipe, "plot 'geometry/dat_files/points_translated.dat' with linespoints lw 2 lc rgb 'green'\n");
    }

    pclose(gnuplotPipe);
}

template<typename T, size_t N>
void GnuPlotting<T, N>::plot() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Line Plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'x-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'y-axis'\n");

    if (N == 3) {
        fprintf(gnuplotPipe, "set zlabel 'z-axis'\n");
        fprintf(gnuplotPipe, "splot 'geometry/dat_files/points.dat' using 1:2:3 with linespoints lw 2 lc rgb 'blue'\n");
    } else {
        fprintf(gnuplotPipe, "plot 'geometry/dat_files/points.dat' using 1:2 with linespoints lw 2 lc rgb 'red'\n");
    }

    pclose(gnuplotPipe);
}

// Function to plot translated polyline
void plotTranslatedPolyline() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Translated Polyline Plot'\n");
    fprintf(gnuplotPipe, "plot 'geometry/dat_files/polyline_translated.dat' with lines lw 2 lc rgb 'green'\n");

    pclose(gnuplotPipe);
}

// Function to plot translated cuboid
void plotTranslatedCuboid() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Translated Cuboid Plot'\n");
    fprintf(gnuplotPipe, "splot 'geometry/dat_files/cuboid_translated.dat' with lines lw 2 lc rgb 'green'\n");

    pclose(gnuplotPipe);
}

// Function to plot cuboid
void plotCuboid() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Cuboid Plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
    fprintf(gnuplotPipe, "set zlabel 'Z-axis'\n");

    fprintf(gnuplotPipe, "splot 'geometry/dat_files/cuboid.dat' with linespoints lw 2 lc rgb 'red'\n");

    pclose(gnuplotPipe);
}


// Explicit template instantiations
template class Point<double, 2>;
template class Point<double, 3>;
template class DataFile<double, 2>;
template class DataFile<double, 3>;
template class GnuPlotting<double, 2>;
template class GnuPlotting<double, 3>;
