// Author: Wayne Wood
#include "Point.h"
#include <iostream>
#include <vector>

using std::cout, std::endl;

int main(int argc, char* argv[]) 
{
    // Create three points
    std::vector <Point> points = {Point(), Point(10, 5), Point(-7)};

    // Output points and their distances to each other by index number
    cout << "\n\n***** Points and their distances *****\n\n";

    for (int i=0, n=points.size(); i<n; ++i) {
        cout << "Point #" << i << ": (" << points[i].get_x_coord() << ", " << points[i].get_y_coord() << ")\n";
        for (int j=0; j<n; ++j) {
            if (i!=j) {
                cout << "\t->\t" << points[i].Distance(points[j]) << " from Point #" << j << endl;
            }
        }
    }

    // Translate the 0th indexed element by 'n' and show updated distances
    float n = 4.5;
    cout << "\n\n***** Adding translation of ->\t" << n << " to point #0 *****\n\n";

    points[0].Translate(n);
    cout << "Translated point #0: (" << points[0].get_x_coord() << ", " << points[0].get_y_coord() << ")\n";

    for (int i=1, n=points.size(); i<n; ++i) {
        cout << "\t->\t" << points[0].Distance(points[i]) << " from Point #" << i << endl;
    }

    // Translate the 0th element by a negative n-value and show updated distances
    n *= -1.5;
    cout << "\n\n***** Adding translation of ->\t" << n << " to point #0 *****\n\n";

    points[0].Translate(n);
    cout << "Translated point #0: (" << points[0].get_x_coord() << ", " << points[0].get_y_coord() << ")\n";

    for (int i=1, n=points.size(); i<n; ++i) {
        cout << "\t->\t" << points[0].Distance(points[i]) << " from Point #" << i << endl;
    }
    cout << endl;
}
