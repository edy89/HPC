//gcc buffon_parallel.c -o buffon_parallel_out  -fopenmp -fPIC -lquadmath -lm 
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <stdbool.h>
#include <quadmath.h>
#include<omp.h>

#define M_PI 3.14159265358979323846 


/*bool corta(double l,double d)
{ 
		__float128 x = d * drand48();
		__float128 y = l * cos(M_PI/2 * drand48()); // se hace uso de pi (M_PI) para la conversion del ángulo que recibe el coseno en gradientes

		if(y > x)
		{
			return true;
		}
		else
			return false;
	
}*/

int main(int argc, char *argv[])
{
	int intentos,i,op,x,N = 0,C = 0;	//N:numero total de intentos/C:numero de veces que una aguja cruza una linea
	double L = 0.25,D = 0.75,start_t, end_t,y,z;	//L:longitud de la aguja/D:interdistancia entre las rectas
	//intentos = 10000000;			
	srand48(time(NULL));
	int precision = 30;
	char out[64],*c; 		//string de salida/ Sizeof sigdig = tamaño (bytes) del string de salida


	op=strtol(argv[1],&c,10);
  	intentos=atoi(argv[1]);

  	start_t = omp_get_wtime();
  	//int hilos = omp_get_num_procs();
  	//omp_set_num_threads(8);
	//printf("Numero de hilos: %d", omp_get_num_procs());
	#pragma omp parallel shared(L,D)
	{
		#pragma omp parallel for reduction(+:N,C) private(z,y)
		for (i = 0; i < intentos; ++i)
		{
		  z = D * drand48();
		  y = L * cos(M_PI/2 * drand48());

		  if(y > z)
		   {
		     ++C;
		   }		 
		
		  ++N;
		}
		#pragma omp flush(N,C)
	}
	end_t = omp_get_wtime();
  	printf("%lf\n",end_t - start_t);
  	__float128  pi_ = (2.0 * L * N) / (D * C);
	quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, pi_);//%#*.30Qg = conversion al formato de salida
	printf("El pi calculado es: %s\n", out);

	return 0;

}
