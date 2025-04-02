#include <iostream>
#include <map>
#include <functional>
#include "../include/shape_handlers.h" // Include the header file for handle functions

using namespace std;

void menu() {
    cout << "What do you want to plot:\n";
    cout << "1. Cuboid\n";
    cout << "2. Sphere\n";
    cout << "3. Triangle\n";
    cout << "4. Cylinder\n";
    cout << "5. Polygon\n";
    cout << "6. Bezier Curve\n";
    cout << "7. 3D Line\n";
    cout << "8. Scene (Combination of Shapes)\n";
    cout << "Enter choice: ";
}

int main() {
    map<int, function<void()>> handlers = {
        {1, handleCuboid},
        {2, handleSphere},
        {3, handleTriangle},
        {4, handleCylinder},
        {5, handlePolygon},
        {6, handleBezier},
        {7, handleLine3D},
        {8, handleScene}
    };

    menu();
    int choice;
    cin >> choice;

    if (handlers.find(choice) != handlers.end()) {
        handlers[choice]();
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
