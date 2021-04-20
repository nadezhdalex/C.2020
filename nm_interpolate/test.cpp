#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "interpolation.h"
#include "l_exception.h"
#include "point.h"

static void test(RRFunc f, Real a, Real b, Real expected_result, int expected_error, char *message) {
    int error = NA_OK;
    Real result = integrate(f, a, b, EPS, &error);
    printf("Integral = %lf\n", result);
    if(expected_error != error) {
    	printf("******* Test FAILED! WRONG ERROR_CODE******* %s\nRight ERROR = %d, Your error = %d\n", message, expected_error, error);
        return;
    }
    if(expected_error == error && error != NA_OK) {
    	printf("Test OK! Right error!\n");
        return;
    }
    if(almost_equal(result, expected_result, EPS)) {
        printf("Test OK!\n");
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\nRight answer = %lf, Your answer = %lf\n", message, expected_result, result);
        return;
    }
}

static Real f1(Real x) {
    return x;
}

static Real f2(Real x) {
    return x*x;
}

static Real f3(Real x) {
	return sin(x);
}

static Real f4(Real x) {
	return cos(x);
}

static Real f5(Real x) {
	return 1/x;
}


int main(void) {
	vector<Point> points(3);
	points[0] ={0, -1};
	points[1] ={1, 1};
	points[2] ={4, 1};
    test(f1, -1, 2, 1.5, NA_OK, "Test 1");
    test(f2, 4, 1, 0, NA_SEGMENT, "Test 2");
    test(f3, 0, 1e+3, 0.43762, NA_OK, "Test 3");
    test(f4, -1e-5, 1e-6, 0.000011000, NA_OK, "Test 4");
    test(f1, 1e+15, 1e+20, 4.9999999995e+39, NA_OK, "Test 5");
    test(f5, 1e-4, 1e-3, 2.30258509299, NA_OK, "Test 6");
    test(f5, 0, 2, 0, NA_DIVERGE, "Test 7");
    return 0; 
}
