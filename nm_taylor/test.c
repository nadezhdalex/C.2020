#include <stdio.h>
#include <math.h>
#include "find_log.h"

static void test(Real x, Real expected_result, int expected_error, char *message) {
    int error = NA_OK;
    Real result = find_log(x, EPS, &error);
    printf("L = %lf\n", result);
    if(expected_error != error) {
    	printf("******* Test FAILED! WRONG ERROR_CODE******* %s\nRight ERROR = %d, Your error = %d\n", message, expected_error, error);
        return;
    }
    if(expected_error == error && error != NA_OK) {
    	printf("Test OK! Right error!\n");
        return;
    }
    if(almost_equal(result, expected_result)) {
        printf("Test OK!\n");
        return;
    }
    else {
        printf("******* Test FAILED! WRONG ANSWER******* %s\nRight answer = %lf, Your answer = %lf\n", message, expected_result, result);
        return;
    }
}

int main(void) {
	test(2, log(2), NA_OK, "Test 1");
    test(1, log(1), NA_OK, "Test 2");
    test(0.55, log(0.55), NA_OK, "Test 3");
    test(6, 0, NA_RANGE, "Test 4");
    test(0.001, log(0.001), NA_OK, "Test 5");
    test(0.6, log(0.6), NA_OK, "Test 6");
    return 0; 
}
