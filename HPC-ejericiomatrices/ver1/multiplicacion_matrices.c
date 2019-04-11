#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//https://computing.llnl.gov/tutorials/parallel_comp/
//https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
int corre(int argc, char *argv[])
{
	
   //argc cuenta la cantidad de datos que llegan en argv
   //Si le llega solo uno es por que solo le llego el nombre del archivo 
    if (argc==1)
   {
       printf("Debes ingresar mas parametros...\n");
       return 1;
   }
   //printf("Hola %c",*argv[1]);

   //char *data[10]=&argv[1];

   char *a;
   a=(char *)argv[1];
   //printf("Holaaa %c",*a);
   

    int x=atoi(a);
    //printf("Holaaaaa %d",x);
    int k,i,j,y,temporal;
    srand (time(NULL));
    

	 
    
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
    	
  /*
  printf("matriz A:");
  for(i=0;i<x;i++)
     {
      printf("\n\t\t");
      for(j=0;j<x;j++)
         {
    printf("[ %d ]", mat[i][j]);
         }
     }
     
  printf("\nmatriz B:");
  for(i=0;i<x;i++)
     {
      printf("\n\t\t");
      for(j=0;j<x;j++)
         {
        printf("[ %d ]", mat2[i][j]);
         }
     }


    printf("\n");
    printf("LA MATRIZ PRODUCTO DE LAS 2 MATRICES INDICADAS ES:\n");
    for(i=0;i<x;i++)
       {
        printf("\n\t\t");
        for(j=0;j<x;j++)
           {
  	    printf("[ %d ]", resultado[i][j]);
	   }
	}
  printf("\n");

*/
return 0;
}
