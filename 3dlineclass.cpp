#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class Point3d{
public:
	double x, y, z;
	Point3d(double x=0, double y =0, double z=0): x(x), y(y), z(z) {}
	void input()
	{cin>> x >> y >> z;}
};

class DataFile{
public:
	void generate(const Point3d& p1,const Point3d& p2){
	ofstream file ("points3d.dat");
	if(!file){
	cerr << "Error in opening the file..." << endl;
	return;
	}
	
	int totalPoints = 10;
	double dx = (p2.x -p1.x)/(totalPoints -1);
	double dy = (p2.y - p1.y)/(totalPoints -1);
	double dz = (p2.z - p1.z)/(totalPoints - 1);
	
	for(int i=0 ; i<totalPoints; i++){
	file << (p1.x + i*dx) << " " << (p1.y + i*dy) << " " << (p1.z + i*dz) << endl;
	}
	file.close();
	}
};

class GnuPlotting{
public:
	void plot(){
	FILE*gnuplotPipe = popen("gnuplot -persistent", "w");
	if (!gnuplotPipe) {
	cerr << "Error opening gnu plot..." << endl;
	return;
	}
	
	fprintf(gnuplotPipe, "set title '3d Line with help of classes'\n");
	fprintf(gnuplotPipe, "set xlabel 'x-axis'\n");
	fprintf(gnuplotPipe, "set ylabel 'y-axis'\n");
	fprintf(gnuplotPipe, "set zlabel 'z-axis'\n");
	fprintf(gnuplotPipe, "set grid\n");
	fprintf(gnuplotPipe, "splot 'points3d.dat' with linespoints lw 2 lc rgb 'red'\n");
	pclose(gnuplotPipe); 
	}
};

int main() {
	Point3d p1, p2;
	DataFile generator;
	GnuPlotting plotter;
	
	cout<< "Enter point a (x1, y1, z1): ";
	p1.input();
	cout << "Enter point b (x2, y2, z2): ";
	p2.input();
	
	generator.generate(p1,p2);
	plotter.plot();
	
	cout<< "3d plot => ..." << endl;
	return 0;
}
