#include <iostream>
#include <cstdlib>
#include <cmath>
#include "my_math.h"

int compareReal(Real x, Real y, Real eps) {
    if(fabs(x - y) < eps * fmax(fmax(x, y), 1.0)) {
        return 0;
    }
    if(x > y) {
        return 1;
    }
    return -1;
}

