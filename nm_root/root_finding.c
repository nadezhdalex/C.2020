#include "root_finding.h"
#include <stdio.h>
#include <math.h>

Real find_root_dichotomy(RRFunc f, Real a, Real b, Real eps, int *err) {
    int error_code = NA_OK;
    Real x = 0;
    int iter = 0;

    if(f(a)*f(b) < 0) {
        while(fabs(b - a) > eps && iter < ITERATION) {
            x = (a + b)/2;
            if(f(b) * f(x) < 0) {
                a = x;
            }
            else {
                b = x;
            }
            iter++;
        }
        if(iter == ITERATION) {
            error_code = NA_Converge;
        }
    }
    else {
        error_code = NA_Segment;
    }

    if(err != NULL) {
        *err = error_code;
    }
    return x;
}
