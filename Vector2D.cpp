#include "Vector2D.h"
#include <iostream>

using namespace std;

Vector2D::Vector2D(){
    x = 0.00;
    y = 0.00;
}

Vector2D::Vector2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}

Vector2D operator*(Vector2D& v1, double d){
    double vecX = v1.x * d;
    double vecY = v1.y * d;
    Vector2D returnVec(vecX, vecY);
    return returnVec;
}
 
Vector2D operator/(Vector2D& v1, double d){
    //initializes values assuming d == 0
    double vecX = v1.x;
    double vecY = v1.y;
    if (d != 0) {
        vecX = vecX/d;
        vecY = vecY/d;
    }
    Vector2D returnVec(vecX, vecY);
    return returnVec;
}

ostream& operator<<(ostream& cout, Vector2D &v1){
    cout << "<" << v1.x << ", " << v1.y << ">";
    return cout;
}