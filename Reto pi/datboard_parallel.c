//gcc -o datboard_parallel_out datboard_parallel.c -fPIC -lquadmath -lm -fopenmp
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<time.h>
#include <quadmath.h>
#include<omp.h>

//#define SEED 35791246
 
int main(int argc, char *argv[])
{
   srand(time(NULL));
   int intentos,w,op; //numero de intentos
   double x,y,z,start_t, end_t;
   int i,count=0; /* # of points in the 1st quadrant of unit circle */
   int precision = 30;
   char out[64],*c;
   //clock_t start_t, end_t;

   op=strtol(argv[1],&c,10) ;
   intentos=atoi(argv[1]);
   //w=intentos;

   start_t = omp_get_wtime();
   #pragma omp parallel
   {
      #pragma omp parallel for private(z,y,x) reduction(+:count)
      for ( i=0; i<intentos; i++) 
      	  {
         	x = (double)rand()/RAND_MAX;
         	y = (double)rand()/RAND_MAX;
         	z = x*x+y*y;

         	if (z <= 1) count++;
         }
      
   }
   end_t = omp_get_wtime();
   printf("%lf\n",end_t - start_t);
   __float128 pi_= (double) count/intentos*4;
   quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, pi_);//%#*.30Qg = conversion al formato de salida
   printf("# of trials= %d ,El pi calculado es: %s\n",intentos, out);
   //duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   //printf("%f\n",duration);
   return 0;
}
