typedef double Real;
#include "errors.h"



/*
    Для квадратной матрицы вычислить обратную, с помощью линейного представления матриц.
        x: заданная точка
        eps: заданная точность
        err: код ошибки.
	
	Возвращаемое значение:
		Функция возвращает f(x) и записывает код ошибки.	
*/

Real** readMatrix(const char *finame, int *nrows, int *ncols, struct NAError *err);
int printMatrix(const char *finame, Real **matrix, int nrows, int ncols, struct NAError *err);
void freeMatrix(Real **matrix, int nrows);
Real det(Real **matrix, int n, struct NAError *err, Real eps);

