#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	
    int k,i,j,x,y,temporal;
    srand (time(NULL));
    
    printf("Introduce la dimension de la matrices: ");
    scanf("%d",&x);
	 
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
    	
    printf("\n");
    printf("***LA MATRIZ PRODUCTO DE LAS 2 MATRICES INDICADAS ES:\n");
    printf("\n");
    for(i=0;i<x;i++)
       {
        printf("\n\t\t");
        for(j=0;j<x;j++)
           {
  	    printf("[ %d ]", resultado[i][j]);
	   }
	}
return 0;
}
