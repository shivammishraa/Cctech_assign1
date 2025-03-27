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
#include "scene.h"

using namespace std;

void menu() {
    cout << "What do you want to plot:\n";
    cout << "1. Cuboid\n";//issue in the diagonls and also see the choices once again
    cout << "2. Triangle\n";//issue in the plot graph need to make it more clear
    cout << "3. Bezier Curve\n";//once again see the logic
    cout << "4. Polygon\n";//issue in 3D check the logic
    cout << "5. Cylinder\n";//working fine but see the choices once again
    cout << "6. Sphere\n";//choices
    cout << "7. Polyline\n";//fine
    cout << "8. 3D Line\n";//fine

    
    cout << "9. Scene (Combination of Shapes)\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;
    menu();
    cin >> choice;

    if (choice == 9) {
        Scene scene;
        int subChoice;
        do {
            cout << "Add shapes to the scene:\n";
            menu();
            cin >> subChoice;

            if (subChoice == 1) {
                double x, y, z, length, width, height;
                cout << "Enter origin (x y z) and dimensions (length width height): ";
                cin >> x >> y >> z >> length >> width >> height;
                scene.addCuboid(x, y, z, length, width, height);
            } else if (subChoice == 2) {
                double x1, y1, z1, x2, y2, z2, x3, y3, z3;
                cout << "Enter vertices (x1 y1 z1), (x2 y2 z2), (x3 y3 z3): ";
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
                scene.addTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
            } else if (subChoice == 3) {
                int numPoints;
                cout << "Enter number of control points: ";
                cin >> numPoints;
                vector<vector<double>> controlPoints(numPoints, vector<double>(3));
                for (int i = 0; i < numPoints; ++i) {
                    cout << "Enter control point " << i + 1 << " (x y z): ";
                    cin >> controlPoints[i][0] >> controlPoints[i][1] >> controlPoints[i][2];
                }
                scene.addBezier(controlPoints);
            } else if (subChoice == 4) {
                int sides;
                cout << "Enter number of sides: ";
                cin >> sides;
                vector<vector<double>> vertices(sides, vector<double>(3));
                for (int i = 0; i < sides; ++i) {
                    cout << "Enter vertex " << i + 1 << " (x y z): ";
                    cin >> vertices[i][0] >> vertices[i][1] >> vertices[i][2];
                }
                scene.addPolygon(sides, vertices);
            } else if (subChoice == 5) {
                double x, y, z, radius, height;
                int segments;
                cout << "Enter origin (x y z), radius, height, and segments: ";
                cin >> x >> y >> z >> radius >> height >> segments;
                scene.addCylinder(x, y, z, radius, height, segments);
            } else if (subChoice == 6) {
                double x, y, z, radius;
                int segments;
                cout << "Enter center (x y z), radius, and segments: ";
                cin >> x >> y >> z >> radius >> segments;
                scene.addSphere(x, y, z, radius, segments);
            } else if (subChoice == 7) {
                int numPoints;
                cout << "Enter number of points: ";
                cin >> numPoints;
                vector<vector<double>> points(numPoints, vector<double>(3));
                for (int i = 0; i < numPoints; ++i) {
                    cout << "Enter point " << i + 1 << " (x y z): ";
                    cin >> points[i][0] >> points[i][1] >> points[i][2];
                }
                for (size_t i = 1; i < points.size(); ++i) {
                    scene.addLine(points[i - 1][0], points[i - 1][1], points[i - 1][2],
                                  points[i][0], points[i][1], points[i][2]);
                }
            } else if (subChoice == 8) {
                double x1, y1, z1, x2, y2, z2;
                cout << "Enter endpoints (x1 y1 z1) and (x2 y2 z2): ";
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                scene.addLine(x1, y1, z1, x2, y2, z2);
            }

            cout << "Do you want to add more shapes? (1 for Yes, 0 for No): ";
            cin >> subChoice;
        } while (subChoice == 1);

        scene.plotScene("data/scene.dat");
    } else {
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
    }

    return 0;
}
