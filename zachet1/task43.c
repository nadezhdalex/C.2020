#include <stdio.h>
#include <stdlib.h>
#include "task43.h"
#include "errors.h"
#include "my_string.h"
#include "string.h"
char** readMatrix(const char *finame, int *nrows, int *ncols, struct NAError *err) {
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
	if(fscanf(fin, "%d%d\n", &rows, &cols) != 2 || rows < 1 || cols < 1) {
        fclose(fin);
		err->code = NA_WRONG_NUMBER;
		err->mes = "Can't read cols or rows. Or they are out of range";
		return NULL;
    }
    
	char **result;
	result = (char**)malloc(rows * cols * sizeof(char*));
	if(result == NULL) {
		fclose(fin);
		err->code = NA_MEMORY;
		err->mes = "Result are out of memory";
		return NULL;
	}
	
	for(int row = 0; row < rows; row++) {
		for(int col = 0; col < cols; col++) {
			result[row * cols + col] = read_string(fin);
			//if(result[row * cols + col] == NULL) {
            	//result[row * cols + col] = malloc(1);
            	//result[row * cols + col][0] = '\0';
			//}
		}
	}
	*nrows = rows;
	*ncols = cols;
	fclose(fin);
	err->code = NA_OK;
	return result;
} 


int printMatrix(const char *finame, char **matrix, int nrows, int ncols, struct NAError *err) {
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
	
	fprintf(fout, "%d %d\n", nrows, ncols);
	for(int i = 0; i < nrows; i++)
	{
		for(int j = 0; j < ncols; j++) {
			fprintf(fout, "%s ", matrix[i * ncols + j]);
			fprintf(fout, "\n");
		}
	}
	
	fclose(fout);
	err->code = NA_OK;
	return err->code;
}


/* Функция поиска строки k
	Параметры:
		char **matrix: матрица слов;
		int n: количество строк;
		int m: количество столбцов.

	Функция ищет строку k матрицы A, такую что обращенное слово R(W(k))
	совпадает с некоторым из слов W(i)
 
	Метод: посимвольно сравниваем строки R(W(k)) и W(i)
	Возращаемое значение: в случае успеха номер строки k, иначе - (-1). 
*/


int search(char **matrix, int n, int m) {
    for(int k = 0; k < n; k++) {
        int k_len = 0;
        for(int i = 0; i < m; i++) {
            k_len += string_length(matrix[k * m + i]);
        }
        for(int j = 0; j < n; j++) {
            int tmp_len = 0;
            for(int i = 0; i < m; i++) {
                tmp_len += string_length(matrix[j * m + i]);
            }
            if (k_len == tmp_len) {
                int flag = 1;
                int k_i = m - 1, k_j = string_length(matrix[k * m + k_i]) - 1;
                int tmp_i = 0, tmp_j = 0;
                while(1) {
                    if(matrix[k * m + k_i][k_j] != matrix[j * m + tmp_i][tmp_j]){
                        flag = 0;
                        break;
                    }
                    k_j--;
                    if(k_j < 0) {
                        k_i--;
                        if(k_i < 0) break;
                        k_j = string_length(matrix[k * m + k_i]) - 1;
                    }
                    tmp_j++;
                    if(tmp_j >= string_length(matrix[j*m + tmp_i])) {
                        tmp_i++;
                        if(tmp_i >= m) break;
                        tmp_j = 0;
                    }
                }
                //printf("%d", flag);
                if(flag) return k;
            }
        }
    }
    return -1;
}


/* Функция сложения строк
	Параметры:
		char **matrix: матрица слов;
		int n: количество строк;
		int m: количество столбцов;
		int k: номер найденной строки.

	"Сложение" найденной строки k и строки p (поэлементное преобразование для каждого q = 0, ..., m-1)
	Приписывание слова A_kq справа от A_pq.
	Возвращаемое значение: в случае успеха 0, иначе -1.

*/

int sum(char **matrix, int n, int m, int k) {
    if(k == -1) {
    return -1;
    }
    for(int i = 0; i < n; i++) {
        if(i == k) continue; 
        for(int j = 0; j < m; j++) {
            strcat(matrix[i * m + j], matrix[k * m + j]);
        }
    }
    return 0;
}

static void freeList(char **list, int len_list) {
    for(int i = 0; i < len_list; i++) {
        free(list[i]);
    }
    free(list);
}


int solve(const char *finame) {
	int n, m;
	struct NAError error;
    error.code = NA_OK;
    char **matrix;
    matrix = readMatrix(finame, &n, &m, &error);
    if(error.code != NA_OK) {
    	return -1;
    }
    int k = -1; 
    k = search(matrix, n, m);
    printf("%d", k);
    sum(matrix, n, m, k);
    printMatrix("result.txt", matrix, n, m, &error);
    freeList(matrix, n * m);
    if(error.code != NA_OK) {
    	return -1;
    }
	return 0;
}
