#include <stdio.h>
#include <stdlib.h>

int main(void)
{
 
    int mat[3][3],mat2[3][3], resultado[3][3];

    int k,i,j,temporal;

    printf("Introduce 9 valores para la primera matriz:\n");
    for(i=0;i<3;i++)
       {
        for(j=0;j<3;j++)
	   {
            scanf("%d",&mat[i][j]);	    
           }
        }
 
    printf("Introduce 9 valores para la segunda matriz:\n");
    for(i=0;i<3;i++)
       {
        for(j=0;j<3;j++)
	   {
            scanf("%d",&mat2[i][j]);
           }
        }
            


    for (i = 0 ; i < 3 ; i++ ) //i para las filas de la matriz resultante
       {
        for (k = 0 ; k < 3 ; k++ ) // k para las columnas de la matriz resultante
           {  
            temporal = 0 ;
            for (j = 0 ; j < 3 ; j++ ) //j para realizar la multiplicacion de 
                {                                   //los elementos   de la matriz
                 temporal += mat[i][j] * mat2[j][k];
                 resultado[i][k] = temporal ;
                }
            }
    	}

	printf("***LA MATRIZ PRODUCTO DE LAS 2 INDICADAS ES:\n");
	
	printf("\n");
	for(i=0;i<3;i++)
	   {
	    printf("\n\t\t");
	    for(j=0;j<3;j++)
	       {
		printf("%d", resultado[i][j]);
	       }
	   }
return 0;
}
