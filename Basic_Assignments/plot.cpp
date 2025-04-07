#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void generateDataFile(double x1, double y1, double x2, double y2) {
    ofstream file("points.dat");
    if (!file) {
        cerr << "Could not open file for writing!" << endl;
        return;
    }

    // Avoid divide-by-zero error
    if (x1 == x2) {
        cerr << "Error: x1 and x2 cannot be the same." << endl;
        return;
    }

    double m = (y2 - y1) / (x2 - x1); // Slope
    double c = y1 - (m * x1);         // Intercept

    int totalPoints = 10;
    double dx = (x2 - x1) / (totalPoints - 1); // Step size

    for (int i = 0; i < totalPoints; i++) {
        double x = x1 + (i * dx);
        double y = (m * x) + c;
        file << x << " " << y << endl;
    }

    file.close();
}

void plotWithGnuplot() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error: Could not start Gnuplot!" << endl;
        return;
    }

    // Plotting commands
    fprintf(gnuplotPipe, "set title 'Generated Line Plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'X'\n");
    fprintf(gnuplotPipe, "set ylabel 'Y'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "plot 'points.dat' using 1:2 with linespoints lw 2 lc rgb 'blue' title 'Generated Line'\n");

    pclose(gnuplotPipe);
}

int main() {
    double x1, y1, x2, y2;

    cout << "Enter first point (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter second point (x2 y2): ";
    cin >> x2 >> y2;

    if (x1 == x2) {
        cerr << "Invalid input: x1 and x2 must not be the same!" << endl;
        return 1;
    }

    generateDataFile(x1, y1, x2, y2);
    plotWithGnuplot();

    cout << "Plot generated. Check the output!" << endl;
    return 0;
}

