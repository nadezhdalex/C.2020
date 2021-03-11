#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "malloc.h"
#include "stdbool.h"
#include "math.h"
#define LENNAME 255

double S_k (double *A, int k); // находит k-частичную сумму массива А
double MS_k (double *A, int size); // находит максимальное значение k-частичных сумм массива A.
double W_d (double *A, int size, double d, double MS);
int del_W_d (double *A, int size, double W_d_A); // 
int max (int n, int m);

int main (int argc, char* argv[]) {
    FILE *finA;
    FILE *finB;
    FILE *fout;
    if(argc != 3) {
    	printf("incorrect number of arguments");
    	return -1;
    }
    finA = fopen(argv[1], "r");
    if(finA == NULL) {
        printf("Could not open file\n");
        return -1;
    }
    
    finB = fopen(argv[2], "r");
    if(finB == NULL) {
        printf("Could not open file\n");
        fclose(finA);
        return -1;
    }
    
    
    fout = fopen("output.txt", "w");
    if(fout == NULL) {
        printf("Could not open file output.txt\n");
        fclose(finA);
        fclose(finB);
        return -1;
    }
	
	int lenA, lenB;
    if(fscanf(finA, "%d", &lenA) != 1 || lenA < 0) {
        printf("Could not read lenth A \n");
        fclose(finA);
        fclose(finB);
        fclose(fout);
        return -1;
    }
    if(fscanf(finB, "%d", &lenB) != 1 || lenB < 0) {
        printf("Could not read lenth B \n");
        fclose(finA);
        fclose(finB);
        fclose(fout);
        return -1;
    }
    
    double *A;
    A = (double*)malloc(lenA * sizeof(double));
    if(A == NULL) {
        printf("Error! memory not allocated.");
	fclose(finA);
        fclose(finB);
        fclose(fout);
        return -1;
    }
    double *B;
    B = (double*)malloc(lenB * sizeof(double));
    if(B == NULL) {
        printf("Error! memory not allocated.");
	fclose(finA);
        fclose(finB);
        fclose(fout);
        return -1;
    }
    
    for(int i = 0; i < lenA; i++) {
    	if (fscanf(finA, "%lf", &A[i]) != 1) {
            printf("Could not read the number.\n");
            fclose(finA);
            fclose(finB);
            fclose(fout);
            return -1;
        }
    }
    
    for(int i = 0; i < lenB; i++) {
    	if (fscanf(finB, "%lf", &B[i]) != 1) {
        	printf("Could not read the number.\n");
            fclose(finA);
            fclose(finB);
            fclose(fout);
            return -1;
        }
    }
    
    // Основная часть
    double MS_A = MS_k(A, lenA);
    double MS_B = MS_k(B, lenB);
    double W_A = W_d(A, lenA, 0.1 , MS_A);
    double W_B = W_d(B, lenB, 0.1 , MS_B);
    lenA = del_W_d (A, lenA, W_A);
    lenB = del_W_d (B, lenB, W_B);
    int K = max(lenA, lenB);
    if(lenA == 0 || lenB == 0) {
    	return -1;
    }
    fprintf(fout, "%d\n", K);
    for(int i = 0; i < K; i++) {
    	fprintf(fout, "%lf\n", A[i % lenA]*B[i % lenB]);
    }
    
        // Очищение памяти
    free(A);
    free(B);
    
    fclose(finA);
    fclose(finB);
    fclose(fout);
    return 0;
}

double S_k (double *A, int k) {
	double s = 0;
	for(int i = 0; i < k + 1; i++) {
		s = s + A[i];
	}
	return s;
}

double MS_k (double *A, int size) {
	double max = S_k(A, 0);
	double t;
	for(int i = 0; i < size; i++) {
		t = S_k(A, i);
		if(t > max) {
			max = t;
		}
	}
	return max;
}

double W_d (double *A, int size, double d, double MS) {
	double s = 0;
	for(int i = 0; i < size; i++) {
		if(fabs (S_k(A, i) - MS) < d) {
			s = s + A[i];
		}
	}
	return s;
}

int del_W_d (double *A, int size, double W_d_A) {
    int l = 0;
    int r = 0;
    while (r < size) {
        if (fabs(A[r]) <= W_d_A) {
            A[l] = A[r];
            l += 1;
        }
        r = r + 1;
    }
    return l;
}

int max (int n, int m) {
	if(m > n) {
		return m;
	}
	else {
		return n;
	}
}
