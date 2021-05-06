#include "matrix_2d.h"
#include <stdio.h>
#include <stdlib.h>
#include "my_math.h"

Real** readMatrix(const char *finame, int *nrows, int *ncols, struct NAError *err) {
	if(finame == NULL) {
		err->code = NA_FILENAME;
		err->mes = "Invalid file name";
		return NULL;
	}
	
	FILE* fin = fopen(finame, "r");
	if(fin == NULL) {
		err->code = NA_CAN_NOT_OPEN_FILE;
		err->mes = "Can't open file";
		return NULL;
	}
	if(nrows == NULL) {
		err->code = NA_NULLPOINTER;
		err->mes = "NULL pointer to rows";
		return NULL;
	}
	if(ncols == NULL) {
		err->code = NA_NULLPOINTER;
		err->mes = "NULL pointer to cols";
		return NULL;
	}
	
	int rows, cols;
	if(fscanf(fin, "%d%d", &rows, &cols) != 2 || rows < 1 || cols < 1) {
        fclose(fin);
		err->code = NA_WRONG_NUMBER;
		err->mes = "Can't read cols or rows. Or they are out of range";
		return NULL;
    }
    
	Real **result;
	result = (Real**)malloc(rows * sizeof(Real*));
	if(result == NULL) {
		fclose(fin);
		err->code = NA_MEMORY;
		err->mes = "Result are out of memory";
		return NULL;
	}
	for(int row = 0; row < rows; row++) {
		result[row] = (Real*)malloc(cols * sizeof(Real));
		if(result[row] == NULL) {
			fclose(fin);
			err->code = NA_MEMORY;
			err->mes = "Result are out of memory";
			return NULL;
		}
	}
	
	for(int row = 0; row < rows; row++) {
		for(int col = 0; col < cols; col++) {
			fscanf(fin, "%lf", &result[row][col]);
		}
	}
	*nrows = rows;
	*ncols = cols;
	fclose(fin);
	err->code = NA_OK;
	return result;
} 

int printMatrix(const char *finame, Real **matrix, int nrows, int ncols, struct NAError *err) {
	if(finame == NULL) {
		err->code = NA_FILENAME;
		err->mes = "Invalid file name";
		return err->code;
	}
	
	FILE* fout = fopen(finame, "w");
	if(fout == NULL) {
		err->code = NA_CAN_NOT_OPEN_FILE;
		err->mes = "Can't open file";
		return err->code;
	}
	
	if(matrix == NULL) {
		err->code = NA_NULLPOINTER;
		err->mes = "NULL pointer to matrix";
		return err->code;
	}
	
	fprintf(fout, "rows: %d, columns: %d\n", nrows, ncols);
	for(int i = 0; i < nrows; i++)
	{
		for(int j = 0; j < ncols; j++)
			fprintf(fout, "%lf ", matrix[i][j]);
		fprintf(fout, "\n");
	}
	
	fclose(fout);
	err->code = NA_OK;
	return err->code;
}

void freeMatrix(Real **matrix, int nrows) {
	for(int i = 0; i < nrows; i++) {
    	free(matrix[i]);
	}
	free(matrix);
}

static void transpose(Real **matrix, int n) {
	Real **T = (Real**)malloc(n * sizeof(Real*));
	for(int i = 0; i < n; i++) {
    	T[i] = (Real*)malloc(n * sizeof(Real));
	}
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			T[i][j] = matrix[i][j];
			
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			matrix[i][j] = T[n - 1 - i][n - 1 - j];
	freeMatrix(T, n);
}

static void swap(Real **matrix, int n, int row_i1, int row_i2) {
	for(int j = 0; j < n; j++) {
		Real temp = matrix[row_i1][j];
		matrix[row_i1][j] = matrix[row_i2][j];
		matrix[row_i2][j] = temp;
	}
}

static void multiply(Real **matrix, int n, int row, Real a) {
	for(int j = 0; j < n; j++)
		matrix[row][j] = a * matrix[row][j];
}

static void plus_str(Real **matrix, int n, int row_i1, int row_i2, Real a) {
	for(int j = 0; j < n; j++)
		matrix[row_i1][j] = matrix[row_i1][j] + a * matrix[row_i2][j];
}

static void diagonal(Real **matrix, int n, struct NAError *err, Real eps) {
	err->code = NA_OK;
	for(int k = 0; k < (n - 1); k++) {
		err->code = NA_MATR_IS_SINGULAR;
		for(int i = k; i < n; i++) {
			if(fabs(matrix[i][k]) > eps) {
				err->code = NA_OK;
				swap(matrix, n, k, i);
				multiply(matrix, n, k, 1.0 / matrix[k][k]);
				break;
			}
		}
		if(err->code == NA_OK) {
			for(int i = k + 1; i < n; i++) {
				plus_str(matrix, n, i, k, -matrix[i][k] / matrix[k][k]);
			}
		}
		else {
			break;
		}
	}
	for(int k = 0; k < n; k++) {
		if(fabs(matrix[k][k]) < eps) {
			err->code = NA_MATR_IS_SINGULAR;
			err->mes = "Matrix is singular";
			return;
		}
	}
}

Real det(Real **matrix, int n, struct NAError *err, Real eps) {
	diagonal(matrix, n, err, eps);
	if(err->code == NA_MATR_IS_SINGULAR) {
		err->code = NA_OK;
		return 0;
	}
	Real determinant = 1.0;
	if(err->code != NA_MATR_IS_SINGULAR) {
		for(int i = 0; i < n; i++) {
			determinant *= matrix[i][i];
		}
	}
	return determinant;
}
