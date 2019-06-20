//gcc -o datboard_out datboard.c -fPIC -lquadmath -lm
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<time.h>
#include <quadmath.h>

//#define SEED 35791246
 
int main(int argc, char* argv)
{
   srand(time(NULL));
   int niter=10000000; //numero de intentos
   double x,y;
   int i,count=0; /* # of points in the 1st quadrant of unit circle */
   double z;
   int precision = 30;
   char out[64]; 

   #pragma omp parallel num_threads(niter)
   {
      #pragma omp parallel for
      for ( i=0; i<niter; i++) 
      	  {
         	x = (double)rand()/RAND_MAX;
         	y = (double)rand()/RAND_MAX;
         	z = x*x+y*y;

         	if (z <= 1) count++;
         }

      #pragma omp flush(count)

      __float128 pi_= (double) count/niter*4;
      quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, pi_);//%#*.30Qg = conversion al formato de salida
      printf("# of trials= %d ,El pi calculado es: %s\n",niter, out);
      //printf("# of trials= %d , estimate of pi is %g \n",niter,pi);
   }
   return 0;
}
