#include "stdio.h"
#include "math.h"
#define PI 3.1415926535897932384626433832795

double X(double t) {
    return sin(2 * PI * t) + 5;
}

double Y(double t) {
    return cos(2 * PI * t + PI / 3);
}
