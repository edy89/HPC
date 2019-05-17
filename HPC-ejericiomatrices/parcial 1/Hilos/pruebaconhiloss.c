/*
 * Javier Abellán. 1 de Abril de 2003
 *
 * Programa de ejemplo de threads.
 *
 * Un único contador y dos threads para modificarlo. Uno lo incrementa y pone
 * su valor en pantalla precedido de la palabra "Padre". El otro lo 
 * decrementa y ponse su valor en pantalla precedido de la palabra "Hilo".
 * Vemos en pantalla como el contador se incrementa y se decrementa 
 * rápidamente.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Prototipo de la función que va a ejecutar el thread hijo */
void *funcionThread (void *parametro);

/* Contador, global para que sea visible desde el main y desde funcionThread */
int contador = 0;

/*
 * Principal
 * Lanza un thread para la función funcionThread.
 * Después de comprobar el posible error, se mete en un bucle infinito
 * incrementando y mostrando el contador.
 */
int main()
{
	/* Identificador del thread hijo */
	pthread_t idHilo;

	/* error devuelto por la función de creación del thread */
	int error;

	/* Creamos el thread.
	 * En idHilo nos devuelve un identificador para el nuevo thread,
	 * Pasamos atributos del nuevo thread NULL para que los coja por defecto
	 * Pasamos la función que se ejecutará en el nuevo hilo
	 * Pasamos NULL como parámetro para esa función. */
	for (int i = 0; i < 10; ++i)
	{
		/* code */
		error = pthread_create (&idHilo, NULL, funcionThread, NULL);

		/* Comprobamos el error al arrancar el thread */
		if (error != 0)
		{
			perror ("No puedo crear thread");
			exit (-1);
		}

	}
	

	/* Bucle infinito para incrementar el contador y mostrarlo en pantalla */
	/*
	while (1)
	{
		contador++;
		printf ("Padre : %d\n", contador);
	}*/
}

/* Funcion que se ejecuta en el thread hijo.*/
void *funcionThread (void *parametro)
{
   /* Bucle infinito para decrementar contador y mostrarlo en pantalla. */
	//while (1)
	//{
		contador++;
		printf ("Hilo  : %d\n", contador);
	//}
}