#include "Point2D.h"
#include "Vector2D.h"
#include <iostream>
#include <math.h>

using namespace std;

Point2D::Point2D(){
    x = 0.00;
    y = 0.00;
}

Point2D::Point2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(Point2D& p1, Point2D& p2){
    double distanceX = abs(p2.x - p1.x);
    double distanceY = abs(p2.y - p1.y);
    return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
}

ostream& operator<<(ostream& cout, Point2D &p1){
    cout << "(" << p1.x << ", " << p1.y << ")";
    return cout;
}

Point2D operator+(Point2D& p1, Point2D& p2){
    double newPointX = p1.x+p2.x;
    double newPointY = p1.x+p2.y;
    Point2D returnPoint(newPointX, newPointY);
    return returnPoint;
}

Vector2D operator-(Point2D& p1, Point2D& p2){
    double vecX = p1.x-p2.x;
    double vecY = p1.y-p2.y;
    Vector2D returnVec(vecX, vecY);
    return returnVec;
} 