#include <stdio.h>
#include <math.h>
#include "matrix_1d.h"
#include "errors.h"
#include <stdlib.h>

static Real find_inverse(const char *finameIN, const char *finameOUT, int *ncols, int *nrows; Real *matrix, struct NAError *err, Real eps) {
	matrix = readMatrix(&finameIN, &nrows, &ncols, &err);
	Real *inverse;
	inverse = (Real*)malloc(n * n * sizeof(Real));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			inverse[i * n + j] = matrix[i * n + j];
	if(err->code != NA_OK) {
		return err->code;
	}
	if(ncols != nrows) {
		err->code = NA_NOT_QUADRATIC;
		err->mes = "Matrix is not quadratic";
		return err->code;
	}
	inverse(inverse, nrows, &err, eps);
	return inverse;
}

static void test(const char *finameIN, const char *finameOUT, int expected_error, char *message) {
	int *ncols, *nrows;
	struct NAError error; 
    error.code = NA_OK;
    Real *matrix; 
    Real result = find_inverse(finameIN, finameOUT, &ncols, &nrows, matrix, &error, EPS);
    if(expected_error != error.code) {
    	printf("******* Test FAILED! WRONG ERROR_CODE******* %s\nRight ERROR = %d, Your error = %d\n Your message = %s\n", message, expected_error, error.code, error.mes);
        return;
    }
    if(expected_error == error && error.code != NA_OK) {
    	printf("Test OK! Right error!\n Your message = %s\n", error.mes);
        return;
    }
    if(check(matrix, result, EPS)) {
        printf("Test OK!\n");
        printMatrix(finameOUT, result, nrows, ncols, &error);
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\n", message);
        printMatrix(finameOUT, result, nrows, ncols, &error);
        return;
    }
}

int main(void) {
    test(input.txt, output.txt, NA_OK, "Test 1");
    return 0; 
}
