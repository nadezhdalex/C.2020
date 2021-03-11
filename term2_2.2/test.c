#include <stdio.h>
#include <math.h>
#include "reduce.c"

Natural sum_of_abs_integer_parts (Natural n, Real x) {
    double cc;
    modf (x, &cc);
    return n + fabs (cc);
}

int main(void) {
    // Natural n = 1;
    Natural n = 0;
    Natural len = 6;
    Real arr[6] = {1.6584, -2.453, 3.46382, -4.4839, 6.28381, 0};
    PFunc f = sum_of_abs_integer_parts;
    //Natural expected_result = 17;
    Natural expected_result = 0;

    Natural result = reduce(f, n, arr, len);
    printf("sum_of_abs_integer_parts = %u\n", result);
    if(result == expected_result) {
        printf("Test OK!\n");
    }
    else {
        printf("******* Test FAILED! *******\n");
    }
    return 0;
}
