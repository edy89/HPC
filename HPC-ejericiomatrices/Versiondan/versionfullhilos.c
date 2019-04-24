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
  int **matrizA,**matrizB,**matriz,dimension, estado,estado2,estado3;
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
    /*
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension ; j++)
           {
          printf("[ %d ]", m -> matrizA[i][j]);
         }
    }
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension ; j++)
           {
          printf("[ %d ]", m -> matrizB[i][j]);
         }
    }
    */


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
void *multiplicar_matricesfila(void *args)
{

  pack_matrices  *m = (pack_matrices *)args;
  int i,j,k,temporal,status,status1;
  status=m->estado;
  status1=status+1;
  //printf("este \n%d estado",status );
  for (i = status ; i < status1 ; i++ ) //i para las filas de la matriz resultante
       {
        for (k = 0 ; k < m->dimension ; k++ ) // k para las columnas de la matriz resultante
           {  
            temporal = 0 ;
            for (j = 0 ; j < m -> dimension ; j++ ) //j para realizar la multiplicacion de 
                { 
                 temporal += m -> matrizA[i][j] * m -> matrizB[j][k];               
                 m -> matriz[i][k] = temporal;
                }
            }


  }
}

void *multiplicar_matricesfila2(void *args)
{

  pack_matrices  *m = (pack_matrices *)args;
  int i,j,k,temporal,status,status1;
  status=m->estado2;
  status1=status+1;
  //printf("este \n%d estado",status );
  for (i = status ; i < status1 ; i++ ) //i para las filas de la matriz resultante
       {
        for (k = 0 ; k < m->dimension ; k++ ) // k para las columnas de la matriz resultante
           {  
            temporal = 0 ;
            for (j = 0 ; j < m -> dimension ; j++ ) //j para realizar la multiplicacion de 
                { 
                 temporal += m -> matrizA[i][j] * m -> matrizB[j][k];               
                 m -> matriz[i][k] = temporal;
                }
            }


  }
}
void *multiplicar_matricesfila3(void *args)
{

  pack_matrices  *m = (pack_matrices *)args;
  int i,j,k,temporal,status,status1;
  status=m->estado3;
  status1=status+1;
  //printf("este \n%d estado",status );
  for (i = status ; i < status1 ; i++ ) //i para las filas de la matriz resultante
       {
        for (k = 0 ; k < m->dimension ; k++ ) // k para las columnas de la matriz resultante
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
    }
    */
}



int main(int argc, char *argv[])
{


    int i,j;
    srand (time(NULL));
    //printf("Hola %lu",op);
    clock_t start_t, end_t;
    double duration;


    
    int parametro,x;
    parametro=atoi(argv[1]);
    x=parametro;

   
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
  int h;
  //impar=(x%3)==0;
  if (x<=2){
  for (h=0;h<x;h++){
    //printf("%d\nacah", h);
    mul_matrices.estado=h;
    pthread_create(&hilo3,NULL,multiplicar_matricesfila,(void *)&mul_matrices);
    pthread_join(hilo3,NULL);

  }}
  else if( x % 2 == 0){
  for (h=0;h<x;){
    //printf("%d\nacah", h);
    //printf("entro a par" );
    mul_matrices.estado=h;
    pthread_create(&hilo3,NULL,multiplicar_matricesfila,(void *)&mul_matrices);
    mul_matrices.estado2=h+1;
    pthread_create(&hilo4,NULL,multiplicar_matricesfila2,(void *)&mul_matrices);
    pthread_join(hilo3,NULL);    
    pthread_join(hilo4,NULL);     
    h=h+2;
  }
  }
  else if(x % 3 == 0){
  for (h=0;h<x;){
    //printf("entro impar"); 
    //printf("%d\nacah", h);
    mul_matrices.estado=h;
    pthread_create(&hilo3,NULL,multiplicar_matricesfila,(void *)&mul_matrices);
    mul_matrices.estado2=h+1;
    pthread_create(&hilo4,NULL,multiplicar_matricesfila2,(void *)&mul_matrices);
    mul_matrices.estado3=h+2;
    pthread_create(&hilo5,NULL,multiplicar_matricesfila3,(void *)&mul_matrices);
    pthread_join(hilo3,NULL);    
    pthread_join(hilo4,NULL);   
    pthread_join(hilo5,NULL);     
    h=h+3;
  }
  }

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

