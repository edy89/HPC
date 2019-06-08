//gcc -o buffon_out serial_buffon_v1.c -fPIC -lquadmath -lm
#include<stdlib.h>
#include<stdio.h>
#include <quadmath.h>
#include<math.h>
#include<time.h>


int main()
{
	srand48(time(NULL));
	int Numcort = 0,intentos = 1000,aux = 0; //Numcort:Cantidad de cortes de una aguja en una linea
	int precision = 30;
	double l = 10.0,d = 20.0;
	char out[64];
	__float128 ang,a,pi_,x,y; 

	while(aux < intentos)
	{
		x = drand48();
		y = drand48();

		a 	= (d / 2.0) * x;
		ang = 180 * y;
		//quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, ang);//%#*.30Qg = conversion al formato de salida
		//printf("el valor es: %s\n", out);
		
		if(a <= ((l / 2) * sin(ang)))
		{
			Numcort += 1;
			//printf("True \n");
		}

		aux += 1;
	}

	pi_ = (2.0 * l) / ((Numcort / intentos) * d);

	quadmath_snprintf(out, sizeof out, "%#*.30Qg", precision, pi_);//%#*.30Qg = conversion al formato de salida
	printf("El pi calculado es: %s\n", out);

	return 0;
}