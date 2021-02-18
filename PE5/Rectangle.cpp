#include "Rectangle.h"


// p1 is the lower left corner
// p2 is the upper right corner
// if you find that not following this guidelines breaks this class, that
// would be considered a bug
Rectangle::Rectangle(Point p1, Point p2): p1_(p1), p2_(p2) {}

// get the width of the rectangle  
// between p1.x and p2.x
int Rectangle::GetWidth() {
    return std::abs (this->p1_.x - this->p2_.x);
}

// get the height of the rectangle
// between p2.y and p2.y
int Rectangle::GetHeight(){
    return std::abs (this->p1_.y - this->p2_.y);
}

// returns true iff this rectangle shares any points with the other one
bool Rectangle::Overlaps(Rectangle& other) {
    return (this->p1_==other.p1_ || 
            this->p2_==other.p2_ ||
            this->p2_==other.p1_ ||
            this->p1_==other.p2_ );
}

// returns the area of this rectangle
int Rectangle::CalculateArea() {
    return abs ((this->p1_.x - this->p2_.x) * (this->p1_.y - this->p2_.y));
}

// moves the bottom left coordinate down one and to the left one
// moves the upper right coordinate up one and to the right one
void Rectangle::Expand() {
    this->p1_ = this->p1_ + -1;
    this->p2_ = this->p2_ + 1;
}

// moves the bottom left coordinate up one and to the right one
// moves the upper right coordinate down one and to the left one
void Rectangle::Shrink() {
    this->p1_ = this->p1_ + 1;
    this->p2_ = this->p2_ + -1;
}
