//cd C:\Users\Edyson\GitHub\HPC\HPC-ejericiomatrices
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

/*void reservar_matrices(int **x,int **y, int **z, int c);
void liberar_matrices(int **x,int **y, int **z, int c);
void llenar_matriz(int **x,int c);
int **multiplicar(int **x,int **y,int c);
void imprimir_matriz(int **x,int c);*/
 
void reservar_matrices(int **x,int **y, int **z, int c)
{
  int i;
  x = (int **)calloc(c,sizeof(int *));
  y= (int **)calloc(c,sizeof(int *));
  z = (int **)calloc(c,sizeof(int *));

  for(i=0;i<c;i++)
     {
      x[i]= (int *)calloc(c,sizeof(int));
      y[i]= (int *)calloc(c,sizeof(int));
      z[i]= (int *)calloc(c,sizeof(int));
     }

  return;
 }

void liberar_matrices(int **x,int **y, int **z, int c)
{
  int i;
  for (i = 0;i < c;i++)
    {
     free(x[i]);
     free(y[i]);
     free(z[i]);
    }
 
  free(x);
  free(y);
  free(z);

  return;
}

void llenar_matriz2(int **x,int c)
{
    int i,j;
    for(i=0;i<c;i++)
       {
        for(j=0;j<c;j++)
           {
            x[i][j] = rand() % 11;     
            printf("%s\n", );
           }
        }

 return;
}

int **llenar_matriz(int c)
{
    int **x;
    int i,j;
    for(i=0;i<c;i++)
       {
        for(j=0;j<c;j++)
           {
            x[i][j] = rand() % 11;     
           }
        }

 return x;
}


int **multiplicar(int **x,int **y,int c)
{
  int i,k,j,temporal,** z;
  for (i = 0 ; i < c ; i++ ) //i para las filas de la matriz resultante
       {
        for (k = 0 ; k < c ; k++ ) // k para las columnas de la matriz resultante
           {  
            temporal = 0 ;
            for (j = 0 ; j < c ; j++ ) //j para realizar la multiplicacion de 
                {                                   //los elementos   de la matriz
                 temporal += x[i][j] * y[j][k];
                 z[i][k] = temporal ;
                }
            }
        }
 return z;
}

void imprimir_matriz(int **x,int c)
{
    int i,j;
    for(i=0;i<c;i++)
       {
        printf("\n\t\t");
        for(j=0;j<c;j++)
           {
            printf("[ %d ]", x[i][j]);
           }
        }
     return;
}



int main(int argc, char *argv[])
{
    srand (time(NULL));

    pid_t pid;
    clock_t start_t, end_t;

    int k,i,j,y,temporal;
    int parametro,x;    
    double duration;
    int **mat,**mat2, **resultado;
    int estadoHijo;    

    parametro = atoi(argv[1]);
    x = parametro;
    printf("%d\n", x);

    //reservar_matrices(mat,mat2,resultado,x);
    //llenar_matriz(mat,x);
    //llenar_matriz(mat2,x);

    start_t = clock();
    pid = fork();

    reservar_matrices(mat,mat2,resultado,x);
    llenar_matriz2(mat,x);

    if (pid == -1) 
      { 
        perror ("No se puede crear proceso");
        exit (-1);
      }
    if (pid > 0)
        {
         //sleep(1);
         //printf("padre" );
         //mat = llenar_matriz(x);
         //llenar_matriz(mat,x);
         //llenar_matriz(mat2,x);
         //imprimir_matriz(mat,x);
         /*imprimir_matriz(mat2,x);
         liberar_matrices(mat,mat2,resultado,x);*/
        /* wait (&estadoHijo);

         if (WIFEXITED(estadoHijo) != 0)
          {
            printf ("Padre : Mi hijo ha salido. Devuelve %d\n", WEXITSTATUS(estadoHijo));
          }*/
         

        }
    if (pid == 0)
        {
         printf("hijito" ); 
         
         //imprimir_matriz(mat,x);
         /*reservar_matrices(mat,mat2,resultado,x);
         llenar_matriz(mat,x);
         llenar_matriz(mat2,x);*/
         //sleep(3);
          //exit(33);
        }

    //imprimir_matriz(mat,x);

    end_t = clock();
    duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //printf("%f\n",duration);
 
    return 0;
}


