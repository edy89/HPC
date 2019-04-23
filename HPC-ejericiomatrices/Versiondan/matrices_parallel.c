#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
void poblar(int **,int ,int );
void mostrar(int **,int ,int );
void multiplicar(void **,void **,void ** );
unsigned long __stdcall mithread( void* pVoid);
typedef struct _Params
{
  int **mat;
  int **mat2;
  int **resultado;
  int dimension;
}Params, *PParams;
 
unsigned long __stdcall mithread( void* pVoid)
{
  PParams *m = (PParams)pVoid;
  int temporal,i,j,k;
  for (i = 0 ; i < m -> dimension ; i++ ) //i para las filas de la matriz resultante
   {
    for (k = 0 ; k < m -> dimension ; k++ ) // k para las columnas de la matriz resultante
       {  
        temporal = 0 ;
        for (j = 0 ; j < m -> dimension ; j++ ) //j para realizar la multiplicacion de 
            { 
             temporal += m -> mat[i][j] * m -> mat2[j][k];               
             m -> resultado[i][k] = temporal;
            }
        }
  }


}
 



int main(void)
{

    int filas,columnas;
    scanf("%d%d",&filas,&columnas);
    int **matriz;
    int x=3;
    pthread_t hilo1,hilo2,hilo3,hilo4,hilo5,hilo6;

    
    matriz= (int**) calloc(filas,sizeof(int *));
    if (matriz == NULL) return 0;
    int i;
    for(i=0;i<filas;i++){
        matriz[i]= (int*) calloc(columnas,sizeof(int ));
        if(matriz[i] == NULL) return 0;
    }

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


    poblar(matriz,filas,columnas);
    //mostrar(matriz,filas,columnas);
    //multiplicar(matriz,matriz,resultado,filas);
    Params params;
    params.mat = matriz;
    params.mat2 = matriz;
    params.dimension = 3;
    CreateThread( 0, 0, &mithread, &params, 0, 0 );

    //pthread_create(&hilo1,NULL,multiplicar,((void *)matriz,(void *)matriz,(void *)resultado));
    //pthread_join(hilo1,NULL);



    mostrar(resultado,filas,columnas);
    return 0;
}
void poblar (int **matriz,int filas,int columnas){
    srand(time(NULL));
    int i,j;
    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            matriz[i][j]= rand()%10;
        }
    }
}


void mostrar (int **matriz,int filas,int columnas){
    int i,j;
    for(i=0;i<filas;i++){
        for(j=0;j<columnas;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    
}


void multiplicar (void **mat,void **mat2,void **resultado){

  int temporal,i,j,x,k;
  x=3;
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
}
