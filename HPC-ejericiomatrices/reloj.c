#include <time.h>
#include <stdio.h>
#include "multiplicacion_matrices.h"

int main () {
   clock_t start_t, end_t, total_t;
   int i;
   char *a[10];
   *a[0]="10"
   start_t = clock();
   //printf("Starting of the program, start_t = %ld\n", start_t);
    
   printf("Going to scan a big loop, start_t = %ld\n", start_t);
   corre(1,*a);
   end_t = clock();
   printf("End of the big loop, end_t = %ld\n", end_t);
   
   //total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   //printf("Total time taken by CPU: %f\n", total_t  );
   //printf("Exiting of the program...\n");

   return(0);
}