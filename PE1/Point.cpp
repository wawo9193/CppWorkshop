// Author: Wayne Wood
#include "Point.h"
#include <iostream>
#include <math.h>

// No default constructor since I used x=0,y=0 in header file, initializer list used
Point::Point(float x, float y):x_coord_(x), y_coord_(y) {}

Point::~Point(){}

// getter methods
float Point::get_x_coord() const { return x_coord_; }

float Point::get_y_coord() const { return y_coord_; }

// setter methods
void Point::set_x_coord(float x) {
    this->x_coord_ = x;
}

void Point::set_y_coord(float y) {
    this->y_coord_ = y;
}

float Point::Distance(Point p) {    
    float euclidean_dist = sqrt (pow (this->x_coord_ - p.x_coord_, 2) + pow (this->y_coord_ - p.y_coord_, 2));
    return euclidean_dist;
}

void Point::Translate(float t) {
    // Translates `this` coord by amount, t

    this->x_coord_ += t;
    this->y_coord_ += t;
}
