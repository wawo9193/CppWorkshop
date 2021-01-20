// Author: Wayne Wood
#include "Point.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

// Your Point should have two constructors: an updated "default" constructor takes one 
// integer, n, and constructs a point of n dimensions at the origin and a second constructor 
// that takes either a vector or an array of integers as an argument.

// No default constructor since I used x=0,y=0 in header file, initializer list used
Point::Point(int dim):coords_(std::vector<int>(dim)), dimensions_(dim) {}

Point::Point(std::vector<int> coords):coords_(coords), dimensions_(coords.size()) {}

// getter methods
int Point::get_coord(int i) const { return coords_.at(i); }

int Point::get_dimensions() const { return this->dimensions_; }

// setter methods
void Point::set_coord(int i, int coord) {
    // int i:       the index of which coordinate to get
    // int coord:   value to change the coordinate to

    coords_[i] = coord;
}

float Point::Distance(Point p) {  
    // Point p:       the point we will obtain the distance from 'this'
    //
    // Functionality: Checks if dimensions are the same between general points,
    //                then calculates the euclidean distance between the points.

    float euclidean_dist = 0.0;
    if (this->dimensions_==p.get_dimensions()) {
        for (int i=0, n=this->dimensions_; i<n; ++i) {
            euclidean_dist += pow (this->coords_.at(i) - p.get_coord(i), 2);
        }
        euclidean_dist = sqrt (euclidean_dist);
    } else {
        std::cout << "Differing element amounts between multi-dimensional points." << std::endl;
        return 0.0;
    }
    return euclidean_dist;
}

void Point::Translate(int t) {
    // int t:           the amt. we will translate all coordinates by.
    //
    // Functionality:   Translates `this` coords_ by amount, t

    std::cout << "\n\n***** Adding translation of " << t << " to point ";
    PrettyPrint();
    std::cout << "*****\n\n";
    for (int i=0, n=this->dimensions_; i<n; ++i) this->coords_[i] += t;
    std::cout << "Point is now: ";
    PrettyPrint();
    std::cout << std::endl;
}

void Point::PrettyPrint() {
    // Functionality:   prints out the coordinates of `this`

    std::cout << "(";
    for (int i=0, n=this->coords_.size()-1; i<n; ++i) {
        std::cout << this->coords_.at(i) << ",";
    }
    std::cout << this->coords_.back() << ")";
}
