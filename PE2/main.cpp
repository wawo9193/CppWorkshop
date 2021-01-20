// Author: Wayne Wood
#include "Point.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) 
{
    // Create three points
    std::vector <Point> points = {Point(3), Point({10, 5, 1}), Point({-7,0,2})};

    // Output points and their distances to each other by index number
    std::cout << "\n\n***** Points and their distances *****\n\n";

    for (int i=0, n=points.size(); i<n; ++i) {
        std::cout << "Point #" << i << ":\t";
        points[i].PrettyPrint();
        for (int k=0; k<n; ++k) {
            if (i!=k) {
                std::cout << "\n\t->\t" << points[i].Distance(points[k]) << " from Point #" << k << std::endl;
            }
        }
    }

    // Translates the 0th indexed element by value 'n' and shows updated distances
    float n = 4.5;
    points[0].Translate(n);

    for (int i=1, n=points.size(); i<n; ++i) {
        std::cout << "\n\t->\t" << points[0].Distance(points[i]) << " from Point #" << i << std::endl;
    }

    // Translates the 0th element by a negative n-value and shows updated distances
    n *= -1.5;
    points[0].Translate(n);

    for (int i=1, n=points.size(); i<n; ++i) {
        std::cout << "\n\t->\t" << points[0].Distance(points[i]) << " from Point #" << i << std::endl;
    }
    std::cout << std::endl;
}
