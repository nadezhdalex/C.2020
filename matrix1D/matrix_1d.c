#include "matrix_1d.h"
#include <stdio.h>
#include "my_math.h"

Real readMatrix(const char *finame, int *nrows, int *ncols, struct NAError *err) {
	if(fileName == NULL) {
		err.code = NA_FILENAME;
		err.message = "Invalid file name";
		return err.code;
	}
	
	FILE* fin = fopen(finame, "r");
	if(fin == NULL) {
		err.code = NA_CAN_NOT_OPEN_FILE;
		err.message = "Can't open file";
		return err.code;
	}
	if(nrows == NULL) {
		err.code = NA_NULLPOINTER;
		err.message = "NULL pointer to rows";
		return err.code;
	}
	if(ncols == NULL) {
		err.code = NA_NULLPOINTER;
		err.message = "NULL pointer to cols";
		return err.code;
	}
	
	int rows, cols;
	if(fscanf(fin, "%d%d%d", &rows, &cols) != 2 || rows < 1 || cols < 1) {
        fclose(fin);
		err.code = NA_WRONG_NUMBER;
		err.message = "Can't read cols or rows. Or they are out of range";
		return err.code;
    }
    
	Real *result;
	result = (Real*)malloc(rows * cols * sizeof(Real));
	if(result == NULL) {
		fclose(fin);
		err.code = NA_MEMORY;
		err.message = "Result are out of memory";
		return err.code;
	}
	
	for(int row = 0; row < rows; row++) {
		for(int col = 0; cols < cols; col++) {
			fscanf(fin, "%lf", &result[row * cols + col]);
		}
	}
	*nrows = rows;
	*ncols = cols;
	fclose(fin);
	err.code = NA_OK;
	return result;
} 

int printMatrix(const char *finame, Real *matrix, int nrows, int ncols, struct NAError *err) {
	if(fileName == NULL) {
		err.code = NA_FILENAME;
		err.message = "Invalid file name";
		return err.code;
	}
	
	FILE* fout = fopen(finame, "w");
	if(fout == NULL) {
		err.code = NA_CAN_NOT_OPEN_FILE;
		err.message = "Can't open file";
		return err.code;
	}
	
	if(matrix == NULL) {
		err.code = NA_NULLPOINTER;
		err.message = "NULL pointer to matrix";
		return err.code;
	}
	
	printf("rows: %d, columns: %d\n", nrows, ncols);
	for(int i = 0; i < nrows; i++)
	{
		for(int j = 0; j < ncols; j++)
			printf("lf ", matrix[i * ncols + j]);
		printf("\n");
	}
	
	fclose(fout);
	err.code = NA_OK;
	return err.code;
}

static void transpose(Real *matrix, int n) {
	Real *T;
	T = (Real*)malloc(n * n * sizeof(Real));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			T[i * n + j] = matrix[i * n + j];
			
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matrix[i * n + j] = T[(n - 1 - i) * n + (n - 1 - j)];
	free(T);
}

static void swap(Real *matrix, int n, int row_i1, int row_i2) {
	for(int j = 0; j < n; j++) {
		Real temp = matrix[row_i1 * n + j];
		matrix[row_i1 * n + j] = matrix[row_i2 * n + j];
		matrix[row_i2 * n + j] = temp;
	}
}

static void multiply(Real *matrix, int n, int row, Real a) {
	for(int j = 0; j < n; j++)
		matrix[row * n + j] = a * matrix[row * n + j];
}

static void plus_str(Real *matrix, int n, int row_i1, int row_i2, Real a) {
	for(int j = 0; j < n; j++)
		matrix[row_i1 * n + j] = matrix[row_i1 * n + j] + a * matrix[row_i2 * n + j];
}

static Real multiplication(Real *A, Real *B, int n) {
	Real *C;
	C = (Real*)malloc(n * n * sizeof(Real));
	for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
        C[n * i + j] = 0;
        for(int k = 0; k < n; k++)
            C[n * i + j] += A[n * i + k] * B[k * n + j];
    }
    return C;
}

static void diagonal(Real *matrix, Real *matrix_dop, int n, struct NAError *err, Real eps) {
	int error = NA_OK;
	for(int k = 0; k < (n - 1); k++) {
		error = NA_MATR_IS_SINGULAR;
		for(int i = k; i < n; i++) {
			if(fabs(matrix[i * n + k]) >= eps) {
				error = NA_OK;
				swap(matrix_dop, n, k, i);
				swap(matrix, n, k, i);

				multiply(matrix_dop, n, k, 1.0 / matrix[k * n + k]);
				multiply(matrix, n, k, 1.0 / matrix[k * n + k]);
				break;
			}
		}
		if(error == NA_OK) {
			for(int i = k + 1; i < n; i++) {
				plus_str(matrix_dop, n, i, k, -matrix[i * n + k] / matrix[k * n + k]);
				plus_str(matrix, n, i, k, -matrix[i * n + k] / matrix[k * n + k]);
			}
		}
		else
			break;
	}
	for(int k = 0; k < n; k++) {
		if(fabs(matrix[k * n + k]) < eps) {
			err.code = NA_MATR_IS_SINGULAR;
			err.message = "Matrix is singular";
			return;
		}
	}
	err.code = NA_OK
}

void inverse(Real *matrix, int n, struct NAError *err, Real eps) {
	Real *matrix_dop;
	matrix_dop = (Real*)malloc(n * n * sizeof(Real));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i == j)
				matrix_dop[i * n + j] = 1;
			else
				matrix_dop[i * n + j] = 0;

	diagonal(matrix, matrix_dop, n, err);
	if(err.code != NA_MATR_IS_SINGULAR) {
		transpose(matrix, n);
		transpose(matrix_dop, n);
		diagonal(matrix, matrix_dop, n, err);
		transpose(matrix_dop, n);
	}
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matrix[i * n + j] = matrix_dop[i * n + j];
	free(matrix_dop);
}

int check(Real *matrix, Real *inverse, int n, Real eps) {
	Real *result;
	result = multiplication(matrix, inverse, n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i == j)
				if(compare(result[i * n + j], 1.0, eps) != 0)
					return 0;
			else
				if(compare(result[i * n + j], 0, eps) != 0)
					return 0;
	return 1;
}
