#include "../include/logic.h"

// Template class for Points
template<typename T, size_t N>
point<T, N>::point() {
    coords.fill(0);
}

template<typename T, size_t N>
void point<T, N>::input() {
    for (size_t i = 0; i < N; i++) {
        cin >> coords[i];
    }
}

// Template class for DataFile
template<typename T, size_t N>
void DataFile<T, N>::generate(const point<T, N>& p1, const point<T, N>& p2) {
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

// Explicit template instantiations
template class point<double, 2>;
template class point<double, 3>;
template class DataFile<double, 2>;
template class DataFile<double, 3>;
template class GnuPlotting<double, 2>;
template class GnuPlotting<double, 3>;
