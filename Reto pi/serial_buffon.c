//gcc -o buffon_out serial_buffon.c -fPIC -lquadmath -lm
//media/edison/5CAC40DEAC40B3F4/Users/Edyson/Desktop/Reto pi#
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <stdbool.h>
#include <quadmath.h>
#include<omp.h>

#define M_PI 3.14159265358979323846 


bool corta(double l,double d)
{
	__float128 x = d * drand48() ;
	__float128 y = l * cos(M_PI/2 * drand48()); // se hace uso de pi (M_PI) para la conversion del ángulo que recibe el coseno en gradientes

	if(y > x)
	{
		return true;
	}
	else
		return false;
}

int main(int argc, char *argv[])
{
	int intentos,i,op,N = 0,C = 0;	//N:numero total de intentos/C:numero de veces que una aguja cruza una linea
	double L = 0.25,D = 0.75,start_t, end_t;	//L:longitud de la aguja/D:interdistancia entre las rectas
	//intentos = 100000;			
	srand48(time(NULL));
	int precision = 30;
	char out[64],*c; 	 		//string de salida/ Sizeof sigdig = tamaño (bytes) del string de salida
	//clock_t start_t, end_t;


  	op=strtol(argv[1],&c,10) ;
  	intentos=atoi(argv[1]);
  	//x=intentos;

	start_t = omp_get_wtime();
	for(i=0;i < intentos;++i)
		{
			if(corta(L,D))
			  {
				++C;
			  }
		 ++N;
		}

	__float128  pi_ = (2.0 * L * N) / (D * C);

  	end_t = omp_get_wtime();
	printf("%lf\n",end_t - start_t);
  	//duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  	//printf("%f\n",duration);

	//__float128  pi_ = (2.0 * L * N) / (D * C);
	quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, pi_);//%#*.30Qg = conversion al formato de salida
	printf("El pi calculado es: %s\n", out);

	return 0;

}
