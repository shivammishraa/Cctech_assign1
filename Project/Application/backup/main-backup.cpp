#include <iostream>
#include "../../geometry/include/shapes.h"  
#include "../../geometry/include/logic.h"

using namespace std;

int main() {
    int choice;
    cout << "Choose an option:\n1. Shape\n2. Line\n";
    cin >> choice;

    if (choice == 1) {
        cout << "Choose shape:\n1. Cuboid\n";
        int shapeChoice;
        cin >> shapeChoice;

        if (shapeChoice == 1) {
            Point<double, 3> origin;
            double length, breadth, height;

            cout << "Enter origin (x y z): ";
            origin.input();
            cout << "Enter length, breadth, height: ";
            cin >> length >> breadth >> height;

            Cuboid<double> cuboid(origin, length, breadth, height);
            cuboid.generate();
            plotCuboid();

            // Translation
            double dx, dy, dz;
            cout << "Enter translation values (dx dy dz): ";
            cin >> dx >> dy >> dz;

            translateCuboid(dx, dy, dz);
            plotTranslatedCuboid();
        }
    } else if (choice == 2) {
        int dimensions;
        cout << "Enter the dimensions (2 or 3): ";
        cin >> dimensions;

        if (dimensions == 2 || dimensions == 3) {
            int lineType;
            cout << "Choose line type:\n1. Straight Line\n2. Polyline\n";
            cin >> lineType;

            // Create objects for data file handling and plotting
            DataFile<double, 2> generator2D;
            DataFile<double, 3> generator3D;
            GnuPlotting<double, 2> plotter2D;
            GnuPlotting<double, 3> plotter3D;

            if (lineType == 1) { // Straight Line
                if (dimensions == 2) {
                    Point<double, 2> p1, p2;
                    cout << "Enter two points (x1 y1) (x2 y2): ";
                    p1.input();
                    p2.input();
                    generator2D.generate(p1, p2);
                    plotter2D.plot();
                } else {
                    Point<double, 3> p1, p2;
                    cout << "Enter two points (x1 y1 z1) (x2 y2 z2): ";
                    p1.input();
                    p2.input();
                    generator3D.generate(p1, p2);
                    plotter3D.plot();
                }
            } else if (lineType == 2) { // Polyline
                int numPoints;
                cout << "Enter number of Points in the Polyline: ";
                cin >> numPoints;

                if (dimensions == 2) {
                    generator2D.generatePolyline(numPoints);
                    plotter2D.plot();

                    // Translation
                    double dx, dy;
                    cout << "Enter translation values (dx dy): ";
                    cin >> dx >> dy;

                    generator2D.translatePolyline(numPoints, {dx, dy});
                    plotter2D.plotTranslated();
                } else {
                    generator3D.generatePolyline(numPoints);
                    plotter3D.plot();

                    // Translation
                    double dx, dy, dz;
                    cout << "Enter translation values (dx dy dz): ";
                    cin >> dx >> dy >> dz;

                    generator3D.translatePolyline(numPoints, {dx, dy, dz});
                    plotter3D.plotTranslated();
                }
            }
        }
    }

    return 0;
}