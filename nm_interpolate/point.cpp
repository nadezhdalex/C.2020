#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "point.h"

Point::Point(Real x, Real y) {
    this -> x = x;
    this -> y = y;
}

int Point::compare(const void *arg1, const void *arg2) {
    Point *A = (Point*)arg1;
    Point *B = (Point*)arg2;
    return compareReal(A -> x, B -> y, EPS);
}

Real Point::get_X() {
    return this -> x;
}

Real Point::get_Y() {
    return this -> y;
}
