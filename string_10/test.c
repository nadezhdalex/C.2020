#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_string.h"

int main(void)
{
    FILE *fin;
    fin = fopen("input.txt","r");
    if(fin == NULL) {
        printf("Could not open the input file");
        return -1;
    }
    FILE *fout;
    fout = fopen("output.txt","w");
    if(fout == NULL) {
        printf("Could not open the output file");
        fclose(fin);
        return -1;
    }

    function_define(fin, fout);
    fclose(fin);
    fclose(fout);
    return 0;
}
