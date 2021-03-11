#include "stdio.h"

/* Determine which areas in the sequence are more - increasing or non-increasing.
Input: open files.
Output: None. */
int find_max_incr_or_non_incr (FILE *fin, FILE *fout);

int main (void){
    FILE *fin;
    FILE *fout;
    int m;
    fin = fopen("input.txt", "r");
    if(fin == NULL) {
        /*Warning: Could not open file */
        printf("Could not open file input.txt\n");
        return -1;
    }
    
    fout = fopen("output.txt", "w");
    if(fout == NULL) {
        /*Warning: Could not open file */
        printf("Could not open file output.txt\n");
        fclose(fin);
        return -1;
    }
    printf ("HI");

    m = find_max_incr_or_non_incr (fin, fout);
    printf ("%d", m);
    fclose(fin);
    fclose(fout);
    return 0;
}

int find_max_incr_or_non_incr (FILE *fin, FILE *fout) {
    double max_sum;
    double previous_number;
    double current_number;
    double current_sum;
    int scanf_res;
    printf ("Hellow");
    if(fscanf(fin, "%lf", &previous_number) != 1) {
        /*Warning: Could not read the first number */
        printf("Could not read the first number\n");
        return -1;
    }
    current_sum = previous_number;
    max_sum = current_sum;

    while(1) {
        scanf_res = fscanf(fin, "%lf", &current_number);
        if(scanf_res == 0) {
            /*Warning: Could not read the number */
            printf("Could not read the number\n");
            return -1;
        }
        else if(scanf_res == EOF) {
            break;
        }
        if(current_number > previous_number) {
            current_sum += current_number;
            previous_number = current_number;
        }
        else {
            if(current_sum > max_sum) {
                max_sum = current_sum;
            }
            previous_number = current_number;
            current_sum = previous_number;
        }
    }
    if(current_sum > max_sum) {
        max_sum = current_sum;
    }
    fprintf(fout, "Max Sum = %lf", max_sum);
    return 0;
}
