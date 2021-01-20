// Author: Wayne Wood
#ifndef POINT_H
#define POINT_H

#include <vector>

class Point{
    // To create a point on an x,y plane and allows you to get distances
    // between two points and translate the referenced point as well.
    // Ex.
    // Point p1(1.5, -2.3);
    // Point p2; // defaults to (0,0)
    // p1.Distance(p2) // gives euclidean distance
    private:
        std::vector<int> coords_;
        int dimensions_;

    public:
        Point(int dim);
        Point(std::vector<int> coords);

        // getter methods
        int get_coord(int) const;
        int get_dimensions() const;

        // setter methods
        void set_coord(int i, int coord);

        // other methods
        float Distance(Point);
        void Translate(int);
        void PrettyPrint();
};

#endif
