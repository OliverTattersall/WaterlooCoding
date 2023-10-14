#include "point.h"


Point Point :: operator+( const Point & other ) const {
    Point res = {x + other.x, y + other.y};
    return res;

}

// int Point :: x () const{
//     return this->x;
// }

// int Point :: y () const{
//     return this->y;
// }

std::istream & operator>>( std::istream & in, Point & point) {
    int x;
    int y;
    in >> x;
    in >> y;
    point.x = x;
    point.y = y;

    return in;
}

std::ostream & operator<<( std::ostream & out, const Point & point ) {
    out << "(" << point.x << "," << point.y << ")";
    return out;
}

