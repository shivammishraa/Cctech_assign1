#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function to generate the data file for plotting
void generateDataFile(double x1, double y1, double z1, double x2, double y2, double z2) {
    ofstream file("points3d.dat");
    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    int totalPoints = 10;

    double dx = (x2 - x1) / (totalPoints - 1);
    double dy = (y2 - y1) / (totalPoints - 1);
    double dz = (z2 - z1) / (totalPoints - 1);

    // Generate and write points in 3D 
    for (int i = 0; i < totalPoints; i++) {
        double x = x1 + i * dx;
        double y = y1 + i * dy;
        double z = z1 + i * dz;
        file << x << " " << y << " " << z << endl;
    }

    file.close();
}

void plotWithGnuplot() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot!" << endl;
        return;
    }

    // Gnuplot commands for 3D plotting (plot is used for 2d whereas splot for plotting in 3d)
    fprintf(gnuplotPipe, "set title '3D Line with 10 Points'\n");
    fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
    fprintf(gnuplotPipe, "set zlabel 'Z-axis'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "splot 'points3d.dat' with linespoints lw 2 lc rgb 'red';\n");
    pclose(gnuplotPipe);
}

int main() {
    double x1, y1, z1, x2, y2, z2;

    // input
    cout << "Enter point a (x1 y1 z1): ";
    cin >> x1 >> y1 >> z1;
    cout << "Enter point b (x2 y2 z2): ";
    cin >> x2 >> y2 >> z2;

    // Generate data file and plot
    generateDataFile(x1, y1, z1, x2, y2, z2);
    plotWithGnuplot();

    cout << "3D plot: " << endl;
    return 0;
}

