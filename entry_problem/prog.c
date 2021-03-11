#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "malloc.h"
#include "limits.h"
#define LENNAME 255
#define TEMPLEN 11
#define COMPLEN (2 * TEMPLEN)
/*
Функция сравнивает два числа по правилу: a > b при "ab" > "ba".
Входное значение: 2 целых неотрицательных числа.
Выход: true, если a > b и false в остальных случаях.
*/
bool comparison (int a, int b);

/*
Функция S(n, m) порождает символьную строку, которая является десятичной записью максимального числа,
которое можно составить приписыванием элементов A(n, 0), A(n, 1), ..., A(n, m-1), A(n, m+1), ... A(n, M-1). Например, [5, 51, 59, 9] ==> "959551"
Входное значение: массив-копия строки n, за исключением элемента A(n,m), size - длина массива-копии, res - порожденная строка.
Выходное значение: нет.
*/
void function_s (int *num, int size, char *res);

/*
Функция копирует строку матрицы A(n, 0), A(n, 1), ..., A(n, m-1), A(n, m+1), ... A(n, M-1) в массив.
Входное значение: исходная матрица,массив, куда копировать, числа n - номер строки и m - номер столбца, М - количество столбцов в матрице.
Выходное значение: нет.
*/
void copy_mass (int **A, int *copy, int n, int m, int M);

/*
Функция ищет в символьной строке S(n, m) количество различных триграмм и сравнивает с числом К.
Входное значение: символьная строка S(n, m) и К.
Выходное значение: true, если количество триграмм больше либо равно К, иначе false.
*/
bool trigramm_search(char *res, int K);

void print_massive(int *arr, int size);

int main (void) {
    FILE *fin;
    FILE *fout;
    char finame[LENNAME];
    int K; int M; int N;
    int result = -1;
    int count = 0;
    int number = INT_MAX;
    
    while(number != 0) {
        count++;
        number /= 10;
    }
    if(count > TEMPLEN) {
    	printf("Заданный размер длинны строки TEMPLEN приведет к переполнению массива\n");
    	return -1;
    }
    
    printf("Enter the file name:\n");
    scanf ("%s", finame);
    fin = fopen(finame, "r");
    if(fin == NULL) {
        printf("Could not open file\n");
        return -1;
    }
    
    fout = fopen("output.txt", "w");
    if(fout == NULL) {
        printf("Could not open file output.txt\n");
        fclose(fin);
        return -1;
    }

    if(fscanf(fin, "%d%d%d", &K, &N, &M) != 3 || K < 0 || N < 0 || M < 0) {
        printf("Could not read K or N or M.\n");
        fclose(fin);
        fclose(fout);
        return -1;
    }
    
    int **A;
    A = (int**)malloc(N * sizeof(int*));
    int *copy;
    copy = (int*)malloc((M - 1) * sizeof(int));
    char *res_func_s;
    res_func_s = (char*)malloc(((M - 1) * TEMPLEN)* sizeof(char));
    int *index;
    index = (int*)malloc(M * sizeof(int));

    for(int i = 0; i < N; i++) {
        A[i] = (int*)malloc(M* sizeof(int));
        for(int j = 0; j < M; j++) {
            if (fscanf(fin, "%d", &A[i][j]) != 1 || A[i][j] < 0) {
                printf("Could not read the number.\n");
                fclose(fin);
                fclose(fout);
                return -1;
            }
        }
    }
    // Основная часть программы
    for(int i = 0; i < N; i++) {
        int s = 0;
        for(int j = 0; j < M; j++) {
            copy_mass(A, copy, i, j, M);
            // printf ("Copy = ");
            // print_massive (copy, M - 1);
            res_func_s[0] = 0;
            function_s(copy, M - 1, res_func_s);
            // printf (" Res_func_s = %s\n", res_func_s);
            if(trigramm_search(res_func_s, K)) {
                s += 1;
                index[j] = 1;
            }
            else {
                index[j] = 0;
            }
        }
        if(s > i/2 + 1) {
            result = s;
            break;
        }
    }

    fprintf(fout, "n = %d\n", result);
    if(result != -1) {
    	fprintf(fout, "Index: ");
        for(int k = 0; k < M; k++) {
            if(index[k] == 1) {
                fprintf(fout, "%d ", k);
            }
        }
    }

    // Очищение памяти
    free(copy);
    free(res_func_s);
    free(index);
    for(int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);

    fclose(fin);
    fclose(fout);
    return 0;
}

bool comparison (int a, int b) {
    char str_a[COMPLEN];
    char str_b[COMPLEN];
    char str_a_copy[COMPLEN];
    sprintf(str_a, "%d", a);
    sprintf(str_b, "%d", b);
    strcpy(str_a_copy, str_a);
    strcat(str_a, str_b);
    strcat(str_b, str_a_copy);
    if(strcmp(str_a, str_b) > 0) {
        return true;
    }
    else {
        return false;
    }
}

void function_s (int *num, int size, char *res) {
    // Bubble sort
    for (int i = 0; i < size - 1; i++) { 
        for (int j = (size - 1); j > i; j--) {
            if (comparison (num[j], num[j - 1])) {
                int temp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = temp;
            }
        }
    }

    char temp_str[TEMPLEN];
    for(int i = 0; i < size; i++) {
        sprintf(temp_str, "%d", num[i]);
        strcat(res, temp_str);
    }
}

void copy_mass (int **A, int *copy, int n, int m, int M) {
    int temp = 0;
    for (int i = 0; i + temp < M; i++) {
        if (i + temp == m) {
	    i--;
	    temp++;
	}
        else {
	    copy[i] = A[n][i + temp];
	    }
    }
}

bool trigramm_search(char *res, int K) {
    int cnt = 0;
    for(int a = 0; a < 10; ++a) {
        for(int b = 0; b < 10; ++b) {
	    	for(int c = 0; c < 10; ++c) {
	        	for(unsigned long int i = 1; i < strlen(res) - 1; ++i) {
		    		if(res[i - 1] == '0' + a && res[i] == '0' + b && res[i + 1] == '0' + c) {
		        		cnt += 1;
		        		break;
		    		}
				}
	    	}
        }
    }
    // printf ("%d\n", cnt);
    if(cnt < K) {
        return false;
    }
    else {
        return true;
    }
}

/* void print_massive (int *arr, int size) {
	for (int i = 0; i < size; i++) {
		printf ("%d ", arr[i]);
	}
}
*/
