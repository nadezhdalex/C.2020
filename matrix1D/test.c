#include <stdio.h>
#include <math.h>
#include "my_math.h"
#include "matrix_1d.h"
#include <stdlib.h>

static Real* find_inverse(const char *finameIN, const char *finameOUT, int *ncols, int *nrows, Real **matrix, struct NAError *err, Real eps) {
	*matrix = readMatrix(finameIN, nrows, ncols, err);
	if(err->code != NA_OK) {
		return NULL;
	}
	if(*ncols != *nrows) {
		err->code = NA_NOT_QUADRATIC;
		err->mes = "Matrix is not quadratic";
		return NULL;
	}
	Real *inverse_matrix;
	//printMatrix(finameOUT, *matrix, *nrows, *ncols, err);
	int n = *nrows;
	inverse_matrix = (Real*)malloc(n * n * sizeof(Real));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			inverse_matrix[i * n + j] = (*matrix)[i * n + j];
	if(err->code != NA_OK) {
		return NULL;
	}
	inverse(inverse_matrix, n, err, eps);
	return inverse_matrix;
}

static void test(const char *finameIN, const char *finameOUT, int expected_error, char *message) {
	int ncols, nrows;
	struct NAError error; 
    error.code = NA_OK;
    Real *matrix;
    Real *result; 
    result = find_inverse(finameIN, finameOUT, &ncols, &nrows, &matrix, &error, EPS);
    int n = nrows;
    if(expected_error != error.code) {
    	printf("******* Test FAILED! WRONG ERROR_CODE******* %s\nRight ERROR = %d, Your error = %d\n,Your message = %s\n", message, expected_error, error.code, error.mes);
    	free(result);
    	free(matrix);
        return;
    }
    if(expected_error == error.code && error.code != NA_OK) {
    	printf("Test OK! Right error!\nYour message = %s\n", error.mes);
    	free(result);
    	free(matrix);
        return;
    }
    if(check(matrix, result, n, EPS)) {
        printf("Test OK!\n");
        printMatrix(finameOUT, result, nrows, ncols, &error);
        free(result);
    	free(matrix);
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\n", message);
        printMatrix(finameOUT, result, nrows, ncols, &error);
        free(result);
    	free(matrix);
        return;
    }
}

int main(void) {
    test("input.txt", "output.txt", NA_OK, "Test 1");
    test("inp1.txt", "out1.txt", NA_OK, "Test 2");
    test("inp2.txt", "out2.txt", NA_NOT_QUADRATIC, "Test 3");
    test("inp3.txt", "out3.txt", NA_MATR_IS_SINGULAR, "Test 4");
    return 0; 
}
