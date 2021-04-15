#include "find_log.h"
#include <stdio.h>
#include <math.h>

int almost_equal(Real x, Real y) {
    return fabs(x - y) < EPS * fmax(fmax(x, y), 1.0);
}

int static isInRange(Real x) {
	return (almost_equal(x, 2) || (x < 2 && x > 0));
}

Real find_log(Real x, Real eps, int *err) {
    int error_code = NA_OK;
    int iter = 0;
    
    if(!isInRange(x)) {
    	error_code = NA_RANGE;
    	if(err != NULL) {
            *err = error_code;
    	}
    	return x;
    }
	
	int n = 1;
	Real member = x - 1;
	Real sum = member;
    while(fabs(member) > eps * fmax(member, 1.0) && iter < ITERATION) {
    	member *= (-1) * member * n / (n + 1);
		sum += member;
		n++;
        iter++;
    }
    
    if(iter >= ITERATION) {
        error_code = NA_CONVERGE;
    }

    if(err != NULL) {
        *err = error_code;
    }
    return sum;
}
