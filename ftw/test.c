#include <stdio.h>
#include <stdlib.h>
#include "function_file.h"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        return -1;
    }
    difference(argv[1], argv[2]);
    return 0;
}
