#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	
    int k,i,j,x,y,temporal;
    srand (time(NULL));
    printf("Introduce la dimension de la matriz A: ");
    scanf("%d",&x);
	 
    int mat[x][x],mat2[x][x], resultado[x][x];



    //printf("Introduce 9 valores para la primera matriz:\n");
    for(i=0;i<x;i++)
       {
        for(j=0;j<x;j++)
	   {
            //scanf("%d",&mat[i][j]);
	    mat[i][j] = rand() % 11;	    
           }
        }
 
    //printf("Introduce 9 valores para la segunda matriz:\n");
    for(i=0;i<x;i++)
       {
        for(j=0;j<x;j++)
	   {
            //scanf("%d",&mat2[i][j]);
	    mat2[i][j]	= rand() % 11;
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

	printf("***LA MATRIZ PRODUCTO DE LAS 2 INDICADAS ES:\n");
	
	printf("\n");
	for(i=0;i<x;i++)
	   {
	    printf("\n\t\t");
	    for(j=0;j<x;j++)
	       {
		    //printf("%c,%d,%c","[", resultado[i][j],"]");
		    printf("[ %d ]", resultado[i][j]);
	       }
	   }
return 0;
}
