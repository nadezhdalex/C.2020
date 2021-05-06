#include <stdio.h>
#include <math.h>
#include "my_math.h"
#include "matrix_2d.h"
#include <stdlib.h>

static Real find_determinant(const char *finameIN, int *ncols, int *nrows, Real ***matrix, struct NAError *err, Real eps) {
	*matrix = readMatrix(finameIN, nrows, ncols, err);
	if(err->code != NA_OK) {
		return -1;
	}
	if(*ncols != *nrows) {
		err->code = NA_NOT_QUADRATIC;
		err->mes = "Matrix is not quadratic";
		return -1;
	}
	return det(*matrix, *nrows, err, eps);
}

static void test(const char *finameIN, Real expected_result, int expected_error, char *message) {
	int ncols = 0, nrows = 0;
	struct NAError error; 
    error.code = NA_OK;
    Real **matrix;
    Real result = 0;
    result = find_determinant(finameIN, &ncols, &nrows, &matrix, &error, EPS);
    freeMatrix(matrix, nrows);
    if(expected_error != error.code) {
    	printf("******* Test FAILED! WRONG ERROR_CODE******* %s\nRight ERROR = %d, Your error = %d\nYour message = %s\n", message, expected_error, error.code, error.mes);
        return;
    }
    if(expected_error == error.code && error.code != NA_OK) {
    	printf("Test OK! Right error!\nYour message = %s\n", error.mes);
        return;
    }
    if(compareReal(result, expected_result, EPS) == 0) {
        printf("Test OK!\n");
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\nYour answer = %lf, Right answer = %lf\n", message, result, expected_result);
        return;
    }
}

int main(void) {
    test("input.txt", -2 , NA_OK, "Test 1");
    test("inp1.txt", -0.733205, NA_OK, "Test 2");
    test("inp2.txt", 0 , NA_NOT_QUADRATIC, "Test 3");
    test("inp3.txt", 0, NA_OK, "Test 4");
    return 0; 
}
