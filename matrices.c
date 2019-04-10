#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
//https://computing.llnl.gov/tutorials/parallel_comp/
//https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf


//-----------------------Multiplicacion Paralelizada---------------------------------//
/*
 void *multiplicar(int x,int mat[][],int mat2[][])
 {
 	int result[x][x],temporal;

	for (i = 0 ; i < x ; i++ ) //i para las filas de la matriz resultante
	       {
	        for (k = 0 ; k < x ; k++ ) // k para las columnas de la matriz resultante
	           {  
	            temporal = 0 ;
	            for (j = 0 ; j < x ; j++ ) //j para realizar la multiplicacion de 
	                {                                   //los elementos   de la matriz
	                 temporal += mat[i][j] * mat2[j][k];
	                 result[i][k] = temporal ;
	                }
	            }
	    	}
	return result;
 }
*/

void *imprimir(void *args)
{
    int i,x,j;
    int resultado = (int *)args;
    printf(resultado);
    /*printf("\n");
    printf("***LA MATRIZ PRODUCTO DE LAS 2 MATRICES INDICADAS ES:\n");
    printf("\n");

    for(i=0;i<x;i++)
       {
        printf("\n\t\t");
        for(j=0;j<x;j++)
           {
  	    printf("[ %d ]", matriz[i][j]);
	   }
	}
    printf("\n");
    return NULL;*/
}

int main(int argc, const char *argv[])
{
	
    int k,i,x,j,y,temporal;
    srand (time(NULL));
    
    printf("Introduce la dimension de la matrices: ");
    scanf("%d",&x);
    //printf("%d",argc);
    //int x = argc;
	
    int mat[x][x],mat2[x][x], resultado[x][x];



    for(i=0;i<x;i++)
       {
        for(j=0;j<x;j++)
	   {
	    mat[i][j] = rand() % 11;	    
           }
        }
 
    
    for(i=0;i<x;i++)
       {
        for(j=0;j<x;j++)
	    {
	     mat2[i][j]	= rand() % 11;
            }
        }
        
            
	printf("\nmatriz A:\n");
	for(i=0;i<x;i++)
	   {
	    printf("\n\t\t");
	    for(j=0;j<x;j++)
	       {
		printf("[ %d ]", mat[i][j]);
	       }
	   }
	   
	printf("\nmatriz B:\n");
	for(i=0;i<x;i++)
	   {
	    printf("\n\t\t");
	    for(j=0;j<x;j++)
	       {
		    printf("[ %d ]", mat2[i][j]);
	       }
	   }

	for (i = 0 ; i < x ; i++ ) //i para las filas de la matriz resultante
	       {
	        for (k = 0 ; k < x ; k++ ) // k para las columnas de la matriz resultante
	           {  
	            temporal = 0 ;
	            for (j = 0 ; j < x ; j++ ) //j para realizar la multiplicacion de 
	                {                                   //los elementos   de la matriz
	                 temporal += mat[i][j] * mat2[j][k];
	                 resultado[i][k] = temporal ;
	                }
	            }
	    	}
	

//pthread_t h1;
pthread_t h2;
int *matriz = resultado;
//pthread_create(&h1,NULL,multiplicar(x,mat[][],mat2[][]),NULL);
pthread_create(&h2,NULL,imprimir,(void *)matriz);

return 0;
}
