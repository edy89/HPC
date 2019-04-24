#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>


typedef struct 
{
	int **matriz,dimension;
	char id;
}pack;


typedef struct 
{
	int **matrizA,**matrizB,**matriz,dimension;
	char id;
}pack_matrices;


void *imprimir(void *args)
{
	pack  *m = (pack *)args;
	int i,j;
	printf("\nMatriz %c: ", m -> id);
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension ; j++)
           {
  	    	printf("[ %d ]", m -> matriz[i][j]);
	   	   }
		}
	printf("\n");
}

/*void *llenar_matriz(void *args)
{
	pack  *m = (pack *)args;
	int i,j,x;

    for(i=0;i < m -> dimension ;i++)
       {
        for(j = 0;j < m -> dimension ; j++)
           {
  	    	m -> matriz[i][j] = rand() % 11;
	   	   }
		}
}*/


void *llenar_matriz(void *args)
{
	pack_matrices  *m = (pack_matrices *)args;
	int i,j,x;

    for(i=0;i < m -> dimension ;i++)
       {
        for(j = 0;j < m -> dimension ; j++)
           {
  	    	m -> matrizA[i][j] = rand() % 11;
	   	   }
		}

	for(i=0;i < m -> dimension ;i++)
       {
        for(j = 0;j < m -> dimension ; j++)
           {
  	    	m -> matrizB[i][j] = rand() % 11;
	   	   }
		}
}


void *multiplicar_matrices(void *args)
{
	pack_matrices  *m = (pack_matrices *)args;
	int i,j,k,temporal;

    for (i = 0 ; i < m -> dimension ; i++ ) //i para las filas de la matriz resultante
       {
        for (k = 0 ; k < m -> dimension ; k++ ) // k para las columnas de la matriz resultante
           {  
            temporal = 0 ;
            for (j = 0 ; j < m -> dimension ; j++ ) //j para realizar la multiplicacion de 
                { 
                 temporal += m -> matrizA[i][j] * m -> matrizB[j][k];               
                 m -> matriz[i][k] = temporal;
                }
            }
    	}
      /*
    printf("%s", "MAtriz Resultado: \n");

    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension ; j++)
           {
  	    	printf("[ %d ]", m -> matriz[i][j]);
	   	   }
		}*/
}


int main(int argc, char *argv[])
{


	int i,j;
    srand (time(NULL));
    char *c;
    long op=strtol(argv[1],&c,10) ;
    //printf("Hola %lu",op);
    clock_t start_t, end_t;
    double duration;


    
    int x=(int)op;
    printf("Holaaaaa %d \n",x);

	 
    pthread_t hilo1,hilo2,hilo3,hilo4,hilo5,hilo6;

    pack packmA,packmB;
    pack_matrices mul_matrices;
    packmA.dimension = x;
    packmB.dimension = x;
    mul_matrices.dimension = x;
    packmA.id = 'A';
    packmB.id = 'B';
    mul_matrices.id = 'R';
    

    //mat = (int **)calloc(x,sizeof(int *));
    packmA.matriz = (int **)calloc(x,sizeof(int *));
    packmB.matriz = (int **)calloc(x,sizeof(int *));
    mul_matrices.matriz = (int **)calloc(x,sizeof(int *));
    mul_matrices.matrizA = (int **)calloc(x,sizeof(int *));
    mul_matrices.matrizB = (int **)calloc(x,sizeof(int *));

    for(i=0;i<x;i++)
       {
       	packmA.matriz[i] = (int *)calloc(x,sizeof(int));
       	packmB.matriz[i] = (int *)calloc(x,sizeof(int));
       	mul_matrices.matriz[i] = (int *)calloc(x,sizeof(int));
       	mul_matrices.matrizA[i] = (int *)calloc(x,sizeof(int));
       	mul_matrices.matrizB[i] = (int *)calloc(x,sizeof(int));
       }
         

	pthread_create(&hilo1,NULL,llenar_matriz,(void *)&mul_matrices);
	//pthread_create(&hilo2,NULL,llenar_matriz,(void *)&packmB);
	pthread_join(hilo1,NULL);
	//mul_matrices.matrizA = packmA.matriz;
	//pthread_join(hilo2,NULL);
	//mul_matrices.matrizB = packmB.matriz;
	//pthread_create(&hilo4,NULL,imprimir,(void *)&packmA);
  //pthread_join(hilo4,NULL);
	//pthread_create(&hilo5,NULL,imprimir,(void *)&packmB);
	//pthread_join(hilo5,NULL);
  start_t = clock();
	pthread_create(&hilo3,NULL,multiplicar_matrices,(void *)&mul_matrices);
	pthread_join(hilo3,NULL);
  end_t = clock();
  duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("%f\n",duration);


	for (i = 0;i < x;i++)
	 {
	  free(packmB.matriz[i]);
	  free(packmA.matriz[i]);
	  free(mul_matrices.matriz[i]);
	  free(mul_matrices.matrizA[i]);
	  free(mul_matrices.matrizB[i]);
	 }
 
	free(packmA.matriz);
	free(packmB.matriz);
	free(mul_matrices.matriz);
	free(mul_matrices.matrizA);
	free(mul_matrices.matrizB);

 return 0;
}



