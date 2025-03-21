#include <iostream>
#include <fstream>
#include <cstdlib>
#include <array>

using namespace std;


// Template class for Points
template<typename T , size_t N > //here T will be for the data type and N will see abt the dimensions.
class point{
public:
	array<T,N>coords; // this array will store both the coords for 2D and 3D.
	point() {coords.fill(0);} // initializes array to 0
	void input (){
		for (size_t i=0; i<N; i++){
		cin >> coords[i];
		} // IF N = 2 it will read x and y.  BUT If N = 3 IT WILL THEN READ X Y AND Z. 
	}
};

// Template class for datafile
template<typename T , size_t N>
class DataFile{
public:
	void generate (const point<T, N>& p1, const point<T,N> & p2) {
	//opens the ponts.dat file for writing in it
	ofstream file("points.dat");
	if(!file){
	cerr << "error opening file " << endl;
	return;
	}
	//this logic for calculating step size and the math logic=>
	int totalpoints = 10;
	array<T,N> step;
	for (size_t i = 0; i<N; i++){
	step[i] = (p2.coords[i] - p1.coords[i])/static_cast<double>(totalpoints-1);
	}
	// generating intermediate points=>
	for (int i = 0; i < totalpoints; i++){
		for(size_t j=0; j< N; j++){
		file << (p1.coords[j] + i*step[j]) << " ";
		}
	file << endl;
	}
	file.close();
	}
};

//Template class for Gnu_plotting=>

template<typename T , size_t N>
class GnuPlotting {
public:
	void plot (){
	FILE*gnuplotPipe = popen("gnuplot -persistent", "w");
	if(!gnuplotPipe){
	cerr << "error opening gnu plot" << endl;
	return;
	}
	fprintf(gnuplotPipe, "set terminal wxt\n");
	fprintf(gnuplotPipe, "set title 'Line plot'\n");
	fprintf(gnuplotPipe, "set xlabel 'x-axis'\n");
	fprintf(gnuplotPipe, "set ylabel 'y-axis'\n");
	//now according condition on what we want 2d or 3d i.e z axis =>
	if(N ==3 ){ //if its a 3d graph
	fprintf(gnuplotPipe, "set zlabel 'z-axis'\n");
	fprintf(gnuplotPipe, "splot 'points.dat' with linespoints lw 2 lc rgb 'red' \n");
	} else{// if its  a 2d plot
	fprintf(gnuplotPipe, "plot 'points.dat' with linespoints lw 2 lc rgb 'blue' \n" );
	}
	pclose(gnuplotPipe);
	}
};

int main() {
	int dimensions;
	cout<< "enter the dimensions:(2 or 3)" ;
	cin>>dimensions;
	
	if(dimensions == 2){
	point<double,2>p1,p2;
	DataFile<double,2>generator;
	GnuPlotting<double,2>plotter;
	
	cout<<"Enter a point a(x1,y1):";
	p1.input();
	cout<<"Enter a point b(x2,y2):";
	p2.input();
	
	generator.generate(p1,p2);
	plotter.plot();
	} else if(dimensions == 3){
	point<double,3>p1,p2;
	DataFile<double,3>generator;
	GnuPlotting<double,3>plotter;
	
	cout<< "Enter point a(x1,y1,z1):";
	p1.input();
	cout<< "Enter point b()x2,y2,z2):";
	p2.input();
	
	generator.generate(p1,p2);
	plotter.plot();
	}else{
	cout<<"Invalid Input given... Try again"<<endl;
	}
	return 0;
}

