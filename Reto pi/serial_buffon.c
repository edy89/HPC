//gcc -o buffon_out serial_buffon_v1.c -fPIC -lquadmath -lm
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include <stdbool.h>
#include <quadmath.h>

#define M_PI 3.14159265358979323846 


bool corta(double l,double d)
{
	__float128 x = d * drand48() ;
	__float128 y = l * cos(M_PI/2 * drand48()); // se hace uso de pi (M_PI) para la conversion del ángulo que recibe el coseno en gradientes

	/*quadmath_snprintf(out1, sizeof out1, "%#*.30Qg", precision, x);//%#*.30Qg = conversion al formato de salida
	printf("%s\n", out1);
	quadmath_snprintf(out2, sizeof out2, "%#*.30Qg", precision, y);//%#*.30Qg = conversion al formato de salida
	printf("%s\n", out2);*/

	if(y > x)
	{
		return true;
	}
	else
		return false;
}

int main()
{
	int intentos,N = 0,C = 0;	//N:numero total de intentos/C:numero de veces que una aguja cruza una linea
	double L = 0.25,D = 0.75;	//L:longitud de la aguja/D:interdistancia entre las rectas
	intentos = 100000;			
	srand48(time(NULL));
	int precision = 30;
	char out[64]; 				//string de salida/ Sizeof sigdig = tamaño (bytes) del string de salida

	while(N < intentos)
		{
			if(corta(L,D))
			  {
				++C;
			  }
		 ++N;
		}

	__float128  pi_ = (2.0 * L * N) / (D * C);
	quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, pi_);//%#*.30Qg = conversion al formato de salida
	printf("El pi calculado es: %s\n", out);

	return 0;

}
