#include "reduce.h"

Natural apply(PFunc f, Natural n, Real x) {
    if(n == 0) {
        printf("Error! Wrong number.\n");
        return 0;
    }
    else {
        return (*f)(n, x);
    }
}

Natural reduce(PFunc f, Natural n, Real *arr, Natural len) {
    if(len == 0) {
        printf("Error! Wrong lenth.\n");
        return 0;
    }
    if(arr == NULL) {
        printf("Error! Null or undefined array.\n");
        return 0;
    }
    if(n == 0) {
        printf("Error! Wrong number.\n");
        return 0;
    }
    if(f == NULL) {
        printf("Error! Null or undefined function.\n");
        return 0;
    }

    Natural value = n;
    for(Natural i = 0; i < len; i++) {
        value = apply(f, value, arr[i]);
    }
    return value;
}

