// Author: Wayne W
#include "Rectangle.h"


// p1 is bottom left coordinate and p2 is top right coordinate,
// representing the rectangle.
Rectangle::Rectangle(Point p1, Point p2): p1_(p1), p2_(p2) {}

int Rectangle::GetWidth() {
    /*
    * @params: none
    * 
    * @return: distance between p1 x and p2 x
    */

    return std::abs (this->p1_.x - this->p2_.x);
}

int Rectangle::GetHeight(){
    /*
    * @params: none
    * 
    * @return: distance between p1 y and p2 y
    */

    return std::abs (this->p1_.y - this->p2_.y);
}

bool Rectangle::Overlaps(Rectangle& other) {
    /*
    * @params:
    *   other - other rectangle that this is compared to
    * 
    * @return: if any of the points equal each other then we define that as an overlap
    */

    bool this_overlaps = ((this->p1_>=other.p1_ && this->p1_<=other.p2_) ||
                          (this->p2_>=other.p1_ && this->p2_<=other.p2_));

    bool other_overlaps = ((other.p1_>=this->p1_ && other.p1_<=this->p2_) ||
                           (other.p2_>=this->p1_ && other.p2_<=this->p2_));

    return this_overlaps || other_overlaps;
}

int Rectangle::CalculateArea() {
    /*
    * @params: none
    * 
    * @return: length times height
    */

    return abs ((this->p1_.x - this->p2_.x) * (this->p1_.y - this->p2_.y));
}

void Rectangle::Expand() {
    /*
    * @params: none
    * @return: none
    * 
    * use struct overloading to move top right coordinate up/forward, 
    * and bottom left coordinate down/back
    */

    this->p1_.x -= 1;
    this->p1_.y -= 1;
    this->p2_.x += 1;
    this->p2_.y += 1;
}

void Rectangle::Shrink() {
    /*
    * @params: none
    * @return: none
    * 
    * use struct overloading to move top right coordinate down/back,
    * and bottom left coordinate up/forward
    */

    this->p1_.x = std::min(this->p2_.x, this->p1_.x + 1);
    this->p1_.y = std::min(this->p2_.y, this->p1_.y + 1);
    this->p2_.x = std::max (this->p1_.x, this->p2_.x - 1);
    this->p2_.y = std::max (this->p1_.y, this->p2_.y - 1);
}
