#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "interpolation.h"
#include "l_exception.h"
#include "point.h"
#include "my_math.h"

static void test(Point *vec, int n, Real x, Real expected_result, int expected_error, const char *message) {
    int error = NA_OK;
    Interpolation *points;
    try {
    	points = new Interpolation(vec, n, EPS);
    }	catch (L_exception &err) {
    	error = err.code();
    }
    Real result;
    if(error == NA_OK) {
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
    if(compareReal(result, expected_result, EPS) == 0) {
        printf("Test OK!\n");
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\nRight answer = %lf, Your answer = %lf\n", message, expected_result, result);
        return;
    }
}

int main() {
	Point points1[] = {{0, -1}, {1, 1}, {4, 1}}; // функция -0.5x^2 + 2.5x - 1
    test(points1, 3, 2, 2, NA_OK, "Test 1");
    Point points2[] = {{0, -1}, {0, -1}, {4, 1}}; 
    test(points2, 3, 2, 2, NA_ABSCISSA , "Test 2");
    test(points1, 3, 18, 2, NA_SEGMENT, "Test 3");
    Point points3[] = {{0, -1}};
    test(points3, 1, 2, 2, NA_TOO_LITTLE, "Test 3");
    return 0; 
}
