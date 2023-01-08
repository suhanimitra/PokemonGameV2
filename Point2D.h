#ifndef POINT2D_H
#define POINT2D_H

#include "Vector2D.h"
#include <iostream>
#include <math.h>

using namespace std;

class Point2D {
    public:
        double x;
        double y; 
        Point2D();
        Point2D(double in_x, double in_y);
};

double GetDistanceBetween(Point2D& p1, Point2D& p2);
ostream& operator<<(ostream& cout, Point2D &p1);
Point2D operator+(Point2D& p1, Point2D& p2);
Vector2D operator-(Point2D& p1, Point2D& p2);

#endif