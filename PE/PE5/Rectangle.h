// Author: Wayne W
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdlib>
#include <algorithm>

struct Point {
  int x;
  int y;

  bool operator==(Point& other) {
    /*
    * @params:
    *   other - the Point `this` is compared to
    * 
    * @return: if the coordinates are the same
    */

    return (x==other.x && y==other.y);
  }

  Point operator+(int n) {
    /*
    * @params:
    *   n - the amount to increment by, can be -/+
    * 
    * @return: the modified Point, `this`
    */

    x = std::max (x + n, 0);
    y = std::max (y + n, 0);
    return *this;
  }
};


class Rectangle {
public:
  Rectangle(Point p1, Point p2);

  int GetWidth();
  int GetHeight();
  Point get_p1() { return p1_; }
  Point get_p2() { return p2_; }

  bool Overlaps(Rectangle& other);
  int CalculateArea();
  void Expand();
  void Shrink();

private:
  Point p1_; // bottom left corner
  Point p2_; // upper right corner
};


#endif // RECTANGLE_H
