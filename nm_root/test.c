#include <stdio.h>
#include <math.h>
#include "root_finding.h"
#define EPS 0.00001

static void test(RRFunc f, Real a, Real b, Real expected_result, int expected_error) {
        int error = NA_OK;
        Real result = find_root_dichotomy(f, a, b, EPS, &error);
        printf("Root = %lf\n", result);
        if(expected_error != error) {
             printf("******* Test FAILED! WRONG ERROR_CODE*******\n");
        }
        else {
            if(expected_error == error && error != NA_OK) {
                printf("Test OK! Right error!\n");
            }
            else if(fabs(result - expected_result) < EPS) {
                printf("Test OK!\n");
            }
            else {
                printf("******* Test FAILED! WRONG ROOT*******\n");
            } 
		}
}

Real f1(Real x) {
    return x;
}

Real f2(Real x) {
    return x*x;
}

Real f3(Real x) {
	return x*x - 1e+40;
}

int main(void) {
    test(f1, -1, 2, 0, 1);
    test(f2, 1, 4, 0, -1);
    test(f3, 0, 1e+50, 1e+20, 1);
    return 0; 
}
