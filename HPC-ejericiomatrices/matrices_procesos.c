#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <string.h>
//https://computing.llnl.gov/tutorials/parallel_comp/
//https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
int main(int argc, char *argv[])
{
	
   int count;
 
  //printf ("This program was called with \"%s\".\n",argv[0]);
  /*
  if (argc > 1)
    {
      for (count = 1; count < argc; count++)
    {
      printf("argv[%d] = %s\n", count, argv[count]);
    }
    }
  else
    {
      printf("The command had no other arguments.\n");
    }
 
  return 0;
  */
   //printf("Hola %c",*argv[1]);
   //printf( "Tamaño de la cadena: %i bytes\n", sizeof arqv[1] );

   char *c;
   int op = strtol(argv[1],&c,10) ;
   //printf("Hola %lu",op);
   clock_t start_t, end_t;
   double duration;

    
    int x=op;
    //printf("Holaaaaa %lu",x);
    int k,i,j,y,temporal;
    srand (time(NULL));



    int **mat,**mat2, **resultado;
    //mat = (int **)calloc(x,sizeof(int *));
    mat = (int **)calloc(x,sizeof(int *));
    mat2= (int **)calloc(x,sizeof(int *));
    resultado = (int **)calloc(x,sizeof(int *));
    
    for(i=0;i<x;i++)
       {
        mat[i]= (int *)calloc(x,sizeof(int));
        mat2[i]= (int *)calloc(x,sizeof(int));
        resultado[i]= (int *)calloc(x,sizeof(int));
       }
	 
    
  
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
            
            

      start_t = clock();
   //printf("Starting of the program, start_t = %ld\n", start_t);
    
   //printf("Going to scan a big loop, start_t = %ld\n", start_t);
   
   
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
      
    	end_t = clock();
      duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
      printf("%f\n",duration);

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


for (i = 0;i < x;i++)
 {
  free(mat[i]);
  free(mat2[i]);
  free(resultado[i]);
 }
 
  free(mat);
  free(mat2);
  free(resultado);

return 0;
}
