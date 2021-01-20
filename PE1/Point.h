// Author: Wayne Wood
#ifndef POINT_H
#define POINT_H

class Point{
    // To create a point on an x,y plane and allows you to get distances
    // between two points and translate the referenced point as well.
    // Ex.
    // Point p1(1.5, -2.3);
    // Point p2; // defaults to (0,0)
    // p1.Distance(p2) // gives euclidean distance
    private:
        float x_coord_;
        float y_coord_;

    public:
        Point(float x = 0.0, float y = 0.0);
        ~Point();

        // getters
        float get_x_coord() const;
        float get_y_coord() const;

        // setters
        void set_x_coord(float);
        void set_y_coord(float);

        // others
        float Distance(Point);
        void Translate(float);
};

#endif
