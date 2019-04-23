#include  <stdio.h>
#include <time.h>
#include <stdlib.h>
void poblar(int **,int ,int );
void mostrar(int **,int ,int );



int main(void)
{

    int filas,columnas;
    scanf("%d%d",&filas,&columnas);
    int **matriz;
    
    matriz= (int**) calloc(filas,sizeof(int *));
    if (matriz == NULL) return 0;
    int i;
    for(i=0;i<filas;i++){
        matriz[i]= (int*) calloc(columnas,sizeof(int ));
        if(matriz[i] == NULL) return 0;
    }
    poblar(matriz,filas,columnas);
    mostrar(matriz,filas,columnas);
    
    
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