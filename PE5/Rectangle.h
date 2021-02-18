#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdlib> // abs
#include <algorithm> // max

struct Point {
  int x;
  int y;

  bool operator==(Point& other) {
    if (x==other.x && y==other.y) return true;
    return false;
  }

  Point operator+(int n) {
    x = std::max (x + n, 0);
    y = std::max (y + n, 0);
    return *this;
  }
};


class Rectangle {
public:
  // p1 is the lower left corner
  // p2 is the upper right corner
  // if you find that not following this guidelines breaks this class, that
  // would be considered a bug
  Rectangle(Point p1, Point p2);

  // get the width of the rectangle  
  // between p1.x and p2.x
  int GetWidth();
  // get the height of the rectangle
  // between p2.y and p2.y
  int GetHeight();

  Point get_p1() { return p1_; }
  Point get_p2() { return p2_; }

  // returns true iff this rectangle shares any points with the other one
  bool Overlaps(Rectangle& other);

  // returns the area of this rectangle
  int CalculateArea();

  // moves the bottom left coordinate down one and to the left one
  // moves the upper right coordinate up one and to the right one
  void Expand();

  // moves the bottom left coordinate up one and to the right one
  // moves the upper right coordinate down one and to the left one
  void Shrink();

private:
  Point p1_; // bottom left corner
  Point p2_; // upper right corner
};


#endif // RECTANGLE_H
