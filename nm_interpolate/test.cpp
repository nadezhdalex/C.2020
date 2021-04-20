#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "interpolation.h"
#include "l_exception.h"
#include "point.h"
#include "my_math.h"

static void test(Point *vec, int n, Real x, Real expected_result, int expected_error, char *message) {
    int error = NA_OK;
    Interpolation *points;
    try {
    	points = new Interpolation(vec, n, x, EPS);
    }	catch (L_exception &err) {
    	error = err.code();
    }
    Real result;
    if(error = NA_OK) {
    	try {
    	result = points -> inter_lagrange(x);
    	}	catch (L_exception &err) {
    	error = err.code();
    	}
    }
    
    printf("Interpolated value = %lf\n", result);
    if(expected_error != error) {
    	printf("******* Test FAILED! WRONG ERROR_CODE******* %s\nRight ERROR = %d, Your error = %d\n", message, expected_error, error);
        return;
    }
    if(expected_error == error && error != NA_OK) {
    	printf("Test OK! Right error!\n");
        return;
    }
    if(compareReal(result, expected_result, EPS)) {
        printf("Test OK!\n");
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\nRight answer = %lf, Your answer = %lf\n", message, expected_result, result);
        return;
    }
}

int main() {
	Point points1[3];
	Point points1[0] ={0, -1};
	Point points1[1] ={1, 1};
	Point points1[2] ={4, 1};
    test(points1, 3, 2, 2, NA_OK, "Test 1");
    return 0; 
}
