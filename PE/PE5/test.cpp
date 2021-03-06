#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

#include "Rectangle.h"

TEST_CASE ( "Constructor test", "[constructor]") {
  SECTION( "Arguments map to correct points" ) {
    Rectangle r(Point{1,2}, Point{3,4});
    Point p1 = r.get_p1();
    Point p2 = r.get_p2();
    REQUIRE( (p1.x==1 && p1.y==2) );
    REQUIRE( (p2.x==3 && p2.y==4) );
  }

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
  SECTION ( "One point in another" ) {
    Rectangle r1(Point{0,0}, Point{1,2});
    Rectangle r2(Point{1,2}, Point{6,3});
    REQUIRE( r1.Overlaps(r2) );
  }

  SECTION ( "Rectangles overlap with equivalent points" ) {
    Rectangle r1(Point{0,0}, Point{4,2});
    Rectangle r2(Point{2,1}, Point{6,3});
    REQUIRE( r1.Overlaps(r2) );
  }

  SECTION ( "Rectangles that do not overlap" ) {
    Rectangle r1(Point{0,0}, Point{1,2});
    Rectangle r2(Point{2,3}, Point{6,3});
    REQUIRE( !r1.Overlaps(r2) );
  }
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
  REQUIRE( p1.x==-1 );
  REQUIRE( p1.y==-1 );
  REQUIRE( p2.x==2 );
  REQUIRE( p2.y==2 );
  REQUIRE( r.GetWidth()==3 );
  REQUIRE( r.GetHeight()==3 );
}

TEST_CASE ( "Shrink test", "[shrink]") {
  Rectangle r(Point{0,0}, Point{0,0});
  r.Shrink();
  Point p1 = r.get_p1();
  Point p2 = r.get_p2();
  REQUIRE( p1.x==0 );
  REQUIRE( p1.y==0 );
  REQUIRE( p2.x==0 );
  REQUIRE( p2.y==0 );
  REQUIRE( r.GetWidth()==0 );
  REQUIRE( r.GetHeight()==0 );
}
