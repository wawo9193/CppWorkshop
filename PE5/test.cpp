#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Rectangle.h"

TEST_CASE ( "Constructor test", "[constructor]") {
  SECTION( "Check Height/Width"  ) {
    Rectangle r(Point{0,0}, Point{5,5});
    REQUIRE( r.GetWidth()==5 );
    REQUIRE( r.GetHeight()==5 );
  }

  SECTION( "Unexpected constructor arguments" ) {
    // backwards order
    Rectangle r1(Point{1000,80}, Point{0,0});
    // negative values
    Rectangle r2(Point{-50,-50}, Point{-1,-1});
  }
}

TEST_CASE ( "Overlap test", "[overlap]") {
  Rectangle r1(Point{0,0}, Point{2,4});
  Rectangle r2(Point{0,0}, Point{6,3});
  REQUIRE( r1.Overlaps(r2) );
}

TEST_CASE ( "Area test", "[area]") {
  Rectangle r(Point{0,0}, Point{1,1});
  REQUIRE( r.CalculateArea()==1 );
}

TEST_CASE ( "Expand test", "[expand]") {
  Rectangle r(Point{0,0}, Point{1,1});
  r.Expand();
  Point p1 = r.get_p1();
  Point p2 = r.get_p2();
  REQUIRE( p1.x>=0 );
  REQUIRE( p1.y>=0 );
  REQUIRE( p2.x==2 );
  REQUIRE( p2.y==2 );
}

TEST_CASE ( "Shrink test", "[shrink]") {
  Rectangle r(Point{0,0}, Point{0,0});
  r.Shrink();
  Point p1 = r.get_p1();
  Point p2 = r.get_p2();
  REQUIRE( p1.x==1 );
  REQUIRE( p1.y==1 );
  REQUIRE( p2.x>=0 );
  REQUIRE( p2.y>=0 );
}
