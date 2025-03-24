#include "../include/logic.h"

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
    ofstream file("points.dat");
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

// Template class for GnuPlotting
template<typename T, size_t N>
void GnuPlotting<T, N>::plot() {
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        cerr << "Error opening Gnuplot" << endl;
        return;
    }

    fprintf(gnuplotPipe, "set terminal wxt\n");
    fprintf(gnuplotPipe, "set title 'Line plot'\n");
    fprintf(gnuplotPipe, "set xlabel 'x-axis'\n");
    fprintf(gnuplotPipe, "set ylabel 'y-axis'\n");


    if (N == 3) {
        fprintf(gnuplotPipe, "set zlabel 'z-axis'\n");

        fprintf(gnuplotPipe, "splot 'points.dat' with linespoints lw 2 lc rgb 'red'\n");
    } else {
        fprintf(gnuplotPipe, "plot 'points.dat' with linespoints lw 2 lc rgb 'blue'\n");
    }

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

    fprintf(gnuplotPipe, "splot 'cuboid.dat' with linespoints lw 2 lc rgb 'red'\n");

    pclose(gnuplotPipe);
}

// Explicit template instantiations
template class Point<double, 2>;
template class Point<double, 3>;
template class DataFile<double, 2>;
template class DataFile<double, 3>;
template class GnuPlotting<double, 2>;
template class GnuPlotting<double, 3>;
