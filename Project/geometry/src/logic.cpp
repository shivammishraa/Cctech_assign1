#include "../include/logic.h"
#include <sstream>
#include <filesystem>
#include <limits.h> // For PATH_MAX
#include <cstdlib>  // For realpath()

using namespace std;
namespace fs = std::filesystem;

// void ensureDatFilesDirectory() {
//     string dir = "geometry/dat_files";
//     if (!fs::exists(dir)) {
//         fs::create_directories(dir);
//     }
// }

// Function to translate a cuboid
void translateCuboid(double dx, double dy, double dz) {
    ensureDatFilesDirectory();
    ifstream fileIn("../../geometry/dat_files/cuboid.dat");
    ofstream fileOut("../../geometry/dat_files/cuboid_translated.dat");

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

        istringstream iss(line); // Extract numbers (x, y, z) from the line
        double x, y, z;
        if (iss >> x >> y >> z) { // Extract three double values from the line
            // Apply translation
            fileOut << (x + dx) << " " << (y + dy) << " " << (z + dz) << endl;
        }
    }

    fileIn.close();
    fileOut.close();
    cout << "Debug: Translated cuboid written to cuboid_translated.dat!" << endl;
}

// Function to plot a cuboid
#include <limits.h> // For PATH_MAX
#include <cstdlib>  // For realpath()

void plotCuboid() {
    ensureDatFilesDirectory();

    // Check if the file exists and is not empty
    std::ifstream file("../../geometry/dat_files/cuboid.dat");
    if (!file || file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: cuboid.dat file not found or is empty. Generate the cuboid data first." << std::endl;
        return;
    }

    // Get the absolute path of the file
    char absolutePath[PATH_MAX];
    if (!realpath("../../geometry/dat_files/cuboid.dat", absolutePath)) {
        std::cerr << "Error: Could not resolve the absolute path of cuboid.dat." << std::endl;
        return;
    }
    std::cout << "Debug: Absolute path of cuboid.dat: " << absolutePath << std::endl;

    // Open Gnuplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error opening Gnuplot" << std::endl;
        return;
    }

    // Pass the absolute path to Gnuplot
    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Cuboid Plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
    fprintf(gnuplotPipe, "set zlabel 'Z-axis'\n");
    fprintf(gnuplotPipe, "splot '%s' with linespoints lw 2 lc rgb 'red'\n", absolutePath);

    pclose(gnuplotPipe);
}

// Function to plot a translated cuboid
void plotTranslatedCuboid() {
    ensureDatFilesDirectory();
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Translated Cuboid Plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
    fprintf(gnuplotPipe, "set zlabel 'Z-axis'\n");
    fprintf(gnuplotPipe, "splot '../../geometry/dat_files/cuboid_translated.dat' with lines lw 2 lc rgb 'green'\n");

    pclose(gnuplotPipe);
}

// Implementation of GnuPlotting methods
void GnuPlotting::plot() {
    cout << "Plotting data using Gnuplot..." << endl;
    // Add Gnuplot commands here if needed
}

void GnuPlotting::plotTranslated() {
    cout << "Plotting translated data using Gnuplot..." << endl;
    // Add Gnuplot commands here if needed
}

// Explicit template instantiations
template class Point<double, 2>;
template class Point<double, 3>;
template class DataFile<double, 2>;
template class DataFile<double, 3>;