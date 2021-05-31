#include <stdio.h>
#include <stdlib.h>
#include "task43.h"
#include "my_string.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: \n");
        printf("\t%s intput.txt", argv[0]);
        return -1;
    }
    return solve(argv[1]);
}
