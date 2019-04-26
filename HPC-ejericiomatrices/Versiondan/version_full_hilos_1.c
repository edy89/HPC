#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>




typedef struct 
{
  int **matrizA,**matrizB,dimension;
  //char id;
}pack_matrices;

typedef struct{
  int n_elem,fila_actual;
  int *v1,*v2,**matriz;
}vector;


void *llenar_matriz(void *args)
{
  pack_matrices  *m = (pack_matrices *)args;
  int i,j,x;
  srand (time(NULL));

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
    
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension; j++)
           {
          printf("[ %d ]", m -> matrizA[i][j]);
         }
    }
    printf("\n-------------------------------------------");
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension; j++)
           {
          printf("[ %d ]", m -> matrizB[i][j]);
         }
    }

    printf("\n");
    
}
/*
int m**;

m = (int **)calloc(v -> n_elem,sizeof(int *));

for(i=0;i<v -> n_elem;i++)
   {
     m[i] = (int *)calloc(v -> n_elem,sizeof(int));
   }
*/

void *multiplicar_filas(void *args)
{
  vector *v = (vector *)args;  
  int i,j,aux;
  /*
  int **m;

  m = (int **)calloc(v -> n_elem,sizeof(int *));

    for(i=0;i<v -> n_elem;i++)
       {
        m[i] = (int *)calloc(v -> n_elem,sizeof(int));
       }*/

  //printf("--------------------------\n");  

  //for(i=0;i < v -> n_elem ;i++)
     //{
  	  aux = 0;
      for(j = 0;j < v -> n_elem ; j++)
        {
         aux += v -> v1[j] * v -> v2[j];
        }

        printf("[%d]\n", aux);
        /*if(v -> fila_actual / v -> n_elem == 0)
         {
           printf("\n\t\t");
         }*/
        
/*
      	printf("Matriz Resultado: \n");
      	for(i = v -> n_elem;i < v -> n_elem;i++)
		 {
		   printf("\n\t\t");
		   for(j = 0;j < v -> n_elem ; j++)
		   {
            m[i][j] = aux;
           }
         }*/
      
     //}
/*
  for(j=0;j<v -> n_elem;j++)
      {
       printf("%d",aux[j]);
      }
      */
  //free(aux);
}

/*------------------------------------MAIN----------------------------------------------------------*/

int main(int argc, char *argv[])
{

//DECLARACION DE VARIABLES
    int i,j,k;
    //srand (time(NULL));
    //printf("Hola %lu",op);
    clock_t start_t, end_t;
    double duration;


    
    int parametro,x,y = 0,z = 0;
    parametro=atoi(argv[1]);
    x=parametro;

   
    pthread_t hilo1,hilo2,hilo3,hilo4,hilo5,hilo6;

    pack_matrices mul_matrices;
    mul_matrices.dimension = x;
    vector *vec;
        
    
    //RESERVA DE MEMORIA PARA LAS MATRICES
    vec = calloc(x,sizeof(vector));
    //vec -> matriz 			 = (int **)calloc(x,sizeof(int *));
    mul_matrices.matrizA = (int **)calloc(x,sizeof(int *));
    mul_matrices.matrizB = (int **)calloc(x,sizeof(int *));

    for(i=0;i<x;i++)
       {
        vec[i].matriz  		    = (int **)calloc(x,sizeof(int *));
        vec[i].matriz[i]		= (int *)calloc(x,sizeof(int));
        mul_matrices.matrizA[i] = (int *)calloc(x,sizeof(int));
        mul_matrices.matrizB[i] = (int *)calloc(x,sizeof(int));
        vec[i].v1               = (int *)calloc(x,sizeof(int));
        vec[i].v2               = (int *)calloc(x,sizeof(int));
        vec[i].n_elem           = x;
       }
         
    pthread_create(&hilo1,NULL,llenar_matriz,(void *)&mul_matrices);
    pthread_join(hilo1,NULL);
    
    for(i=0;i < vec -> n_elem ;i++)
       {
        for(j = 0;j < vec -> n_elem ; j++)
          {
          	for(k=0;k< vec -> n_elem;k++)
          	{
             vec[i].v1[k] = mul_matrices.matrizA[i][k];
             vec[i].v2[k] = mul_matrices.matrizB[k][j];
             vec[i].fila_actual = j;
            }
            pthread_create(&hilo2,NULL,multiplicar_filas,(void *)&vec[i]);
            pthread_join(hilo2,NULL);
            //mul_matrices.matriz[i][j] = aux;
          }
        //vec[i].fila_actual = i;
       }
    
    for (i = 0;i < x;i++)
     {
      free(mul_matrices.matrizA[i]);
      free(mul_matrices.matrizB[i]);
      //free(vec[i].matriz);
      //free(vec[i].matriz[i]);
      free(vec[i].v1);
      free(vec[i].v2);
     }
    
    free(vec);
    //free(vec -> matriz);
    free(mul_matrices.matrizA);
    free(mul_matrices.matrizB);

 return 0;
}
