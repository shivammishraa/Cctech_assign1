#include "../include/shapes.h"

template<typename T>
Cuboid<T>::Cuboid(Point<T, 3> origin, T length, T breadth, T height)
    : origin(origin), length(length), breadth(breadth), height(height) {}

template<typename T>
void Cuboid<T>::generate() {
    ofstream file("cuboid.dat");
    if (!file) {
        cerr << "Error opening file" << endl;
        return;
    }

    T x = origin.coords[0];
    T y = origin.coords[1];
    T z = origin.coords[2];
// here we write the bottom face of the cuboid and close it as it consist of 4 points and 5 pts to close the shape
    file << x << " " << y << " " << z << endl;
    file << x + length << " " << y << " " << z << endl;
    file << x + length << " " << y + breadth << " " << z << endl;
    file << x << " " << y + breadth << " " << z << endl;
    file << x << " " << y << " " << z << endl << endl;
  //this endl insures that it will not connect the top and the bottom face.
    // file << endl;
//here we just increase the z axix to form the top face and connect it as well.
    file << x << " " << y << " " << z + height << endl;
    file << x + length << " " << y << " " << z + height << endl;
    file << x + length << " " << y + breadth << " " << z + height << endl;
    file << x << " " << y + breadth << " " << z + height << endl;
    file << x << " " << y << " " << z + height << endl << endl;
  //this endl insures that it will not connect the top and the bottom face.
    // file << endl;

    file.close();
}

// Explicit template instantiation
template class Cuboid<double>;
