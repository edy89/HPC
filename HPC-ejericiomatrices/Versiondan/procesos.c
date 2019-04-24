#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
//#include <string.h>
//https://computing.llnl.gov/tutorials/parallel_comp/
//https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf
int main(int argc, char *argv[])
{
  //Declaracion de variables 
  int count;
  srand (time(NULL));
  char *c;
  int op;
  clock_t start_t, end_t;
  double duration;
  int x;
  int k,i,j,y,temporal;

  //Casteo de variables (char a int llega desde el terminal)
  op=strtol(argv[1],&c,10) ;
  int parametro;
  parametro=atoi(argv[1]);
  x=parametro;

  //Reservamos memoria para las matrices con calloc las llenamos de 0
  int **mat,**mat2, **resultado;
  mat = (int**) calloc(x,sizeof(int *));
  mat2= (int**) calloc(x,sizeof(int *));
  resultado = (int**) calloc(x,sizeof(int *));


  if (mat == NULL) return 0;
  if (mat2 == NULL) return 0;
  if (resultado == NULL) return 0;
  for(i=0;i<x;i++){
      mat[i]= (int *)calloc(x,sizeof(int ));
      mat2[i]= (int *)calloc(x,sizeof(int ));
      resultado[i]= (int *)calloc(x,sizeof(int ));
      if(mat[i] == NULL) return 0;
      if(mat2[i] == NULL) return 0;
      if(resultado[i] == NULL) return 0;
  }


  //LLenamos la primera matriz con numeros randoms
  for(i=0;i<x;i++){
      for(j=0;j<x;j++){
       mat[i][j] = rand()%10;     
         }
      }
  //LLenamos la segunda matriz con numeros randoms
  for(i=0;i<x;i++){
      for(j=0;j<x;j++){
       mat2[i][j] = rand()%10;     
         }
      }


  //Multiplicamos las matrices y les tomamos el tiempo
  


  printf("hola" );  

  //Dificultades, resultados raros, opinion de los datos atipicos, analisis con conclusiones

  //int h;
  //for (h=0;h<x;h++){
  pid_t pid,pid2;  
  int estado;
  int status1, status2;
  if ( (pid=fork()) == 0 )
  { 
      //printf("Soy el hijo (%d, hijo de %d)\n", getpid(),getppid();
      //printf("%d aca", h);
      

          for (estado = 0 ; estado < x ;estado++  ) //i para las filas de la matriz resultante
          {

          //printf("%d estado", estado);    
          if ( (pid2=fork()) == 0 ){

           //start_t = clock();
            
          printf("%d estado", estado);    
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

           else{
             wait(&status2);
           }   
        }

      //end_t = clock();      
      //duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
      //printf("%f\n",duration);

  }
  else
  {

      wait(&status1); 
      //printf("Soy el padre (%d, hijo de %d)\n", getpid(),
      //getppid());
      
  }
  
    



  
    

  /*
  //Impresion de matrices
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

    sleep(1);
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

//Liberamos espacop
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


