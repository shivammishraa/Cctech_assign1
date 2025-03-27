#include <iostream>
#include <fstream>
#include <string>
#include "cuboid.h"
#include "triangle.h"
#include "bezier.h"
#include "polygon.h"
#include "cylinder.h"
#include "sphere.h"
#include "polyline.h"
#include "line3D.h"

using namespace std;

void menu() {
    cout << "What do you wnat to plot:\n";
    cout << "1. Cuboid\n";
    cout << "2. Triangle\n";
    cout << "3. Bezier Curve\n";
    cout << "4. Polygon\n";
    cout << "5. Cylinder\n";
    cout << "6. Sphere\n";
    cout << "7. Polyline\n";
    cout << "8. 3D line\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    menu();
    cin >> choice;

    if (choice == 1) {
        // Cuboid 
        double length, width, height;
        cout << "Enter length, width, height: ";
        cin >> length >> width >> height;

        Cuboid cuboid(length, width, height);
        cuboid.plotCuboid("data/original_cuboid.dat");

        char transform;
        cout << "Do you want to apply transformation? (y/n): ";
        cin >> transform;
        if (transform == 'y') {
            double dx, dy, dz;
            cout << "Enter translation values (dx dy dz): ";
            cin >> dx >> dy >> dz;
            cuboid.translate(dx, dy, dz);

            double sx, sy, sz;
            cout << "Enter scaling factors (sx sy sz): ";
            cin >> sx >> sy >> sz;
            cuboid.scale(sx, sy, sz);

            double angle;
            char axis;
            cout << "Enter rotation angle and axis (x/y/z): ";
            cin >> angle >> axis;
            cuboid.rotate(angle, axis);
        }
        cuboid.plotCuboid("data/transformed_cuboid.dat");

    } else if (choice == 2) {
        //triangle 
        double x1, y1, z1, x2, y2, z2, x3, y3, z3;
        cout << "Enter first vertex (x y z): ";
        cin >> x1 >> y1 >> z1;
        cout << "Enter second vertex (x y z): ";
        cin >> x2 >> y2 >> z2;
        cout << "Enter third vertex (x y z): ";
        cin >> x3 >> y3 >> z3;

        Triangle triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
        string filename = "data/triangle.dat";
        triangle.plotTriangle(filename);

        char transform;
        cout << "Do you want to apply transformations? (y/n): ";
        cin >> transform;

        if (transform == 'y') {
            int option;
            cout << "1. Translate\n2. Scale\n3. Rotate\n";
            cin >> option;

            if (option == 1) {
                double dx, dy, dz;
                cout << "Enter translation values (dx dy dz): ";
                cin >> dx >> dy >> dz;
                triangle.translate(dx, dy, dz);
            } else if (option == 2) {
                double sx, sy, sz;
                cout << "Enter scaling factors (sx sy sz): ";
                cin >> sx >> sy >> sz;
                triangle.scale(sx, sy, sz);
            } else if (option == 3) {
                double angle, Px, Py, Pz;
                char axis;
                cout << "Enter rotation angle: ";
                cin >> angle;
                cout << "Enter rotation axis (x/y/z): ";
                cin >> axis;
                cout << "Enter rotation point (Px Py Pz): ";
                cin >> Px >> Py >> Pz;
                triangle.rotate(angle, axis, Px, Py, Pz);
            }
        }

        triangle.plotTriangle("data/triangle_transformed.dat");
        

    } else if (choice == 3) {
         // Bezier curve
         Bezier bezier;
         int numPoints;
         cout << "Enter the number of control points: ";
         cin >> numPoints;
     
         for (int i = 0; i < numPoints; i++) {
             double x, y, z;
             cout << "Enter coordinates for point " << i + 1 << " (x y z): ";
             cin >> x >> y >> z;
             bezier.addControlPoint(x, y, z);
         }
     
         string filename = "data/bezier.dat";
         bezier.plotBezier(filename);
     
         char transform;
         cout << "Do you want to apply transformations? (y/n): ";
         cin >> transform;
     
         if (transform == 'y') {
             int option;
             cout << "1. Translate\n2. Scale\n3. Rotate\n";
             cin >> option;
     
             if (option == 1) {
                 double dx, dy, dz;
                 cout << "Enter translation values (dx dy dz): ";
                 cin >> dx >> dy >> dz;
                 bezier.translate(dx, dy, dz);
             } else if (option == 2) {
                 double sx, sy, sz;
                 cout << "Enter scaling factors (sx sy sz): ";
                 cin >> sx >> sy >> sz;
                 bezier.scale(sx, sy, sz);
             } else if (option == 3) {
                 double angle;
                 char axis;
                 cout << "Enter rotation angle and axis (x/y/z): ";
                 cin >> angle >> axis;
                 bezier.rotate(angle, axis);
             }
         }
     
         bezier.plotBezier("data/bezier_transformed.dat");
        
    } else if (choice == 4) {
         // Polygon
         int sides;
         cout << "Enter number of sides: ";
         cin >> sides;
 
         Polygon polygon(sides);
 
         for (int i = 0; i < sides; i++) {
             double x, y, z;
             cout << "Enter coordinates for vertex " << i + 1 << " (x y z): ";
             cin >> x >> y >> z;
             polygon.addVertex(x, y, z);
         }
 
         string filename = "data/polygon.dat";
         polygon.plotPolygon(filename);
 
         char transform;
         cout << "Do you want to apply transformations? (y/n): ";
         cin >> transform;
 
         if (transform == 'y') {
             int option;
             cout << "1. Translate\n2. Scale\n3. Rotate\n";
             cin >> option;
 
             if (option == 1) {
                 double dx, dy, dz;
                 cout << "Enter translation values (dx dy dz): ";
                 cin >> dx >> dy >> dz;
                 polygon.translate(dx, dy, dz);
             } else if (option == 2) {
                 double sx, sy, sz;
                 cout << "Enter scaling factors (sx sy sz): ";
                 cin >> sx >> sy >> sz;
                 polygon.scale(sx, sy, sz);
             } else if (option == 3) {
                 double angle;
                 char axis;
                 cout << "Enter rotation angle and axis (x/y/z): ";
                 cin >> angle >> axis;
                 polygon.rotate(angle, axis);
             }
         }
 
         polygon.plotPolygon("data/polygon_transformed.dat");
 
        

    } else if (choice == 5) {
        // Cylinder 
        double radius, height;
        int segments;
        cout << "Enter radius, height, and number of segments: ";
        cin >> radius >> height >> segments;

        Cylinder cylinder(radius, height, segments);
        cylinder.plotCylinder("data/original_cylinder.dat");

        char transform;
        cout << "Do you want to apply transformation? (y/n): ";
        cin >> transform;
        if (transform == 'y') {
            double dx, dy, dz;
            cout << "Enter translation values (dx dy dz): ";
            cin >> dx >> dy >> dz;
            cylinder.translate(dx, dy, dz);

            double sx, sy, sz;
            cout << "Enter scaling factors (sx sy sz): ";
            cin >> sx >> sy >> sz;
            cylinder.scale(sx, sy, sz);

            double angle;
            char axis;
            cout << "Enter rotation angle and axis (x/y/z): ";
            cin >> angle >> axis;
            cylinder.rotate(angle, axis);
        }
        cylinder.plotCylinder("data/transformed_cylinder.dat");
       
    } else if (choice == 6) {
        // Sphere
        double radius;
        int segments;
        cout << "Enter radius and number of segments: ";
        cin >> radius >> segments;

        Sphere sphere(radius, segments);
        sphere.plotSphere("data/original_sphere.dat");

        char transform;
        cout << "Do you want to apply transformation? (y/n): ";
        cin >> transform;
        if (transform == 'y') {
            double dx, dy, dz;
            cout << "Enter translation values (dx dy dz): ";
            cin >> dx >> dy >> dz;
            sphere.translate(dx, dy, dz);

            double s;
            cout << "Enter scaling factor: ";
            cin >> s;
            sphere.scale(s);
        }
        sphere.plotSphere("data/transformed_sphere.dat");

    } else if (choice == 7) {
        // polyline
        Polyline polyline;
        int numPoints;
        cout << "Enter the number of points in the polyline: ";
        cin >> numPoints;

        for (int i = 0; i < numPoints; i++) {
            double x, y, z;
            cout << "Enter coordinates for point " << i + 1 << " (x y z): ";
            cin >> x >> y >> z;
            polyline.addPoint(x, y, z);
        }

        string filename = "data/polyline.dat";
        polyline.plotPolyline(filename);

        char transform;
        cout << "Do you want to apply transformations? (y/n): ";
        cin >> transform;

        if (transform == 'y') {
            int option;
            cout << "1. Translate\n2. Scale\n3. Rotate\n";
            cin >> option;

            if (option == 1) {
                double dx, dy, dz;
                cout << "Enter translation values (dx dy dz): ";
                cin >> dx >> dy >> dz;
                polyline.translate(dx, dy, dz);
            } else if (option == 2) {
                double sx, sy, sz;
                cout << "Enter scaling factors (sx sy sz): ";
                cin >> sx >> sy >> sz;
                polyline.scale(sx, sy, sz);
            } else if (option == 3) {
                double angle;
                char axis;
                cout << "Enter rotation angle and axis (x/y/z): ";
                cin >> angle >> axis;
                polyline.rotate(angle, axis);
            }
        }

        polyline.plotPolyline("data/polyline_transformed.dat");
       
    } else if (choice == 8) {
        // 3D line
        Line3D line;
        double x1, y1, z1, x2, y2, z2;
        cout << "Enter first point (x1 y1 z1): ";
        cin >> x1 >> y1 >> z1;
        cout << "Enter second point (x2 y2 z2): ";
        cin >> x2 >> y2 >> z2;

        line.setPoints(x1, y1, z1, x2, y2, z2);
        string filename = "data/line3D.dat";
        line.plotLine(filename);

        char transform;
        cout << "Do you want to apply transformations? (y/n): ";
        cin >> transform;

        if (transform == 'y') {
            int option;
            cout << "1. Translate\n2. Scale\n3. Rotate\n";
            cin >> option;

            if (option == 1) {
                double dx, dy, dz;
                cout << "Enter translation values (dx dy dz): ";
                cin >> dx >> dy >> dz;
                line.translate(dx, dy, dz);
            } else if (option == 2) {
                double sx, sy, sz;
                cout << "Enter scaling factors (sx sy sz): ";
                cin >> sx >> sy >> sz;
                line.scale(sx, sy, sz);
            } else if (option == 3) {
                double angle;
                char axis;
                cout << "Enter rotation angle and axis (x/y/z): ";
                cin >> angle >> axis;
                line.rotate(angle, axis);
            }
        }

        line.plotLine("data/line3D_transformed.dat");
    }
    
    else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
