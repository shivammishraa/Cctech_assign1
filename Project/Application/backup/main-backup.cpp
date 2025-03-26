#include <iostream>
#include "../../geometry/include/shapes.h"
#include "../../geometry/include/logic.h"
#include "../../geometry/include/cylinder.h"

using namespace std;

int main() {
    int choice;
    cout << "Choose an option:\n1. Shape\n2. Line\n";
    cin >> choice;

    if (choice == 1) { // **Shape Selection**
        cout << "Choose shape:\n1. Cuboid\n2. Cylinder\n";
        int shapeChoice;
        cin >> shapeChoice;

        if (shapeChoice == 2) { // **Cylinder Handling**
            Point<double, 3> center;
            double radius, height;
            int segments;

            cout << "Enter center (x y z): ";
            center.input();
            cout << "Enter radius and height: ";
            cin >> radius >> height;
            cout << "Enter the number of segments for the cylinder: ";
            cin >> segments;

            Cylinder<double> cylinder(radius, height, segments, center);

            // Plot the original cylinder
            system("gnuplot -p -e \"set terminal wxt; splot '../../geometry/dat_files/cylinder.dat' with lines\"");

            char transformationChoice;

            // **Translation**
            cout << "Do you want to translate the cylinder? (y/n): ";
            cin >> transformationChoice;
            if (transformationChoice == 'y' || transformationChoice == 'Y') {
                double dx, dy, dz;
                cout << "Enter translation values (dx dy dz): ";
                cin >> dx >> dy >> dz;
                cylinder.translate(dx, dy, dz);

                // Plot the translated cylinder
                system("gnuplot -p -e \"set terminal wxt; splot '../../geometry/dat_files/cylinder_translated.dat' with lines\"");
            }

            // **Rotation**
            cout << "Do you want to rotate the cylinder? (y/n): ";
            cin >> transformationChoice;
            if (transformationChoice == 'y' || transformationChoice == 'Y') {
                double angle;
                char axis;
                cout << "Enter rotation angle (degrees): ";
                cin >> angle;
                cout << "Enter rotation axis (x, y, z): ";
                cin >> axis;

                cylinder.rotate(angle, axis);

                // Plot the rotated cylinder
                system("gnuplot -p -e \"set terminal wxt; splot '../../geometry/dat_files/cylinder_rotated.dat' with lines\"");
            }

            // **Scaling**
            cout << "Do you want to scale the cylinder? (y/n): ";
            cin >> transformationChoice;
            if (transformationChoice == 'y' || transformationChoice == 'Y') {
                double factor;
                cout << "Enter scaling factor: ";
                cin >> factor;
                cylinder.scale(factor);

                // Plot the scaled cylinder
                system("gnuplot -p -e \"set terminal wxt; splot '../../geometry/dat_files/cylinder_scaled.dat' with lines\"");
            }
        }
    }

    return 0;
}