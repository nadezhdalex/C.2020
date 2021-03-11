#include "stdio.h"
#include "math.h"
int main (void){
    FILE *fin;
    FILE *fout;
    double X;
    double current;
    double eps;
    int res;
    
    fin = fopen ("input.txt", "r");
    if( fin == NULL){
        /*Warning: Could not open file */
        printf ("Could not open file\n");
        return -1;
    }
    
    fout = fopen ("output.txt", "w");
    if( fout == NULL){
        /*Warning: Could not open file */
        printf ("Could not open file\n");
        return -1;
    }

    printf ("Enter a real number:\nX = ");
    if (scanf ("%lf", &X) == 0){
        /*Warning: Could not read the number */
        printf ("Could not read the number");
        return -1;
    }
    printf ("Enter a real number:\neps = ");
    if (scanf ("%lf", &eps) == 0){
        /*Warning: Could not read the number */
        printf ("Could not read the number");
        return -1;
    }

    while (1){
    	res = fscanf(fin, "%lf",&current);
        if (res == 0){
            /*Warning: Could not read the number */
            printf ("Could not read the number");
            return -1;
        }
        else if (res == EOF){
            break; 
        }
        if (fabs (X - current) < eps){
            fprintf (fout, "YES");
            fclose (fin);
            fclose (fout);
            return 0;
        }
    }
    fprintf (fout, "NO");
    fclose (fin);
    fclose (fout);
    return 0;
}
