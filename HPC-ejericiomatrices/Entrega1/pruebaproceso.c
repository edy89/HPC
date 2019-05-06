#include<stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/mman.h>
# include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//https://www.geeksforgeeks.org/fork-system-call/

typedef struct 
{
  int **matrizA,**matrizB,dimension;
  //char id;
}pack_matrices;
typedef struct{
  int n_elem,fila_actual,num;
  int *v1,*v2,**matriz;

  pthread_mutex_t mutex;

}vector;


void *llenar_matriz(void *args)
{
  pack_matrices  *m = (pack_matrices *)args;
  int i,j,x;
  srand (time(NULL));

    for(i=0;i < m -> dimension ;i++)
       {
        for(j = 0;j < m -> dimension ; j++)
           {
          m -> matrizA[i][j] = rand() % 10;
         }
    }

  for(i=0;i < m -> dimension ;i++)
       {
        for(j = 0;j < m -> dimension ; j++)
           {
          m -> matrizB[i][j] = rand() % 10;
         }
    }
    
    /*
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension; j++)
           {
          printf("[ %d ]", m -> matrizA[i][j]);
         }
    }
    printf("\n-------------------------------------------");
    for(i=0;i < m -> dimension ;i++)
       {
        printf("\n\t\t");
        for(j = 0;j < m -> dimension; j++)
           {
          printf("[ %d ]", m -> matrizB[i][j]);
         }
    }
    */
    //printf("\n");
    
}

void multiplicar_filas(int contador,void *args)
{
  vector *v = (vector *)args;  
  int i,j,k,aux,aux2,estado,num;
  //printf("alo %d%d",contador,v[contador].fila_actual);

  aux=0;
  aux2=0;
  //pthread_mutex_lock(&v->mutex);

  //contador=v[0].num;
  estado=v[contador].fila_actual+1;

  

  //printf("%d\nfila", v[0].num);

  for(i= v[contador].fila_actual ; i < estado ; i++)
  {  

    for(k=0;k < v[contador].n_elem ; k++)
    {  
      for(j = 0;j < v[contador].n_elem ; j++)
      {
       //printf("%d esta es i \n ",i );
       //printf("%d esta es j \n ",j );
       //printf("DATO %d \n",v[i].v1[j]);
       //printf("DATO %d \n",v[k].v2[j]); 
       aux += v[i].v1[j] * v[k].v2[j];
       /*
       for(k=0;k < v -> n_elem;k++)
       {
         v->matriz[i][i]=aux;
         printf("DATOo %d \n",v->v1[j]);
         printf("DATOo %d \n",v[estado].v2[j]); 
         aux2 += v->v1[j] * v[estado].v2[j];
         v->matriz[i][i]=aux;
      }*/

       //printf("este es %d", v[i].v1[j]);
       //printf("%d\n",aux );
      }
      v[0].matriz[i][k]=aux;
      //printf("[%d]\n", aux);
      aux = 0;

    }
    //v[0].num=v[0].num+1;
  }


  //pthread_mutex_unlock(&v->mutex);
  //printf("ADIOS");

      
}
int **m3;
pid_t pid;
key_t clave;	//Clave de acceso a la zona de memoria
long int id;	//Identificador de la zona de memoria
int *pmem=NULL;	//Puntero a la zona de memoria

int main(int argc, char *argv[]) {

  	//Creamos un área de memoria compartida
  	clave=ftok("/bin/ls",33); //Cualquier fichero existente y cualquier int
  	id=shmget(clave,sizeof(int)*100,0777|IPC_CREAT);
  	pmem=(int *)shmat(id,(char *)0,0);

    //DECLARACION DE VARIABLES
    int i,j,k;
    int n= 10;
    int status=0;
    clock_t start_t, end_t;
    double duration;
    int parametro,x,u,y = 0,z = 0;
    parametro=atoi(argv[1]);
    x=parametro;
    pthread_t hilo1,hilo2,hilo3,hilo4,hilo5,hilo6;

    pack_matrices mul_matrices;
    mul_matrices.dimension = x;
    vector *vec;
      
    //RESERVA DE MEMORIA
    mul_matrices.matrizA = (int **)calloc(x,sizeof(int *));
    mul_matrices.matrizB = (int **)calloc(x,sizeof(int *));
    m3=(int **)mmap(NULL,sizeof(int *)*x, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas

    for (int i=0; i<x; i++){
      m3[i]=(int *)mmap(NULL,sizeof(int)*x, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //Reservar memoria para filas
    }

    vec = calloc(x,sizeof(vector));

    for(i=0;i<x;i++)
       {

        mul_matrices.matrizA[i] = (int *)calloc(x,sizeof(int));
        mul_matrices.matrizB[i] = (int *)calloc(x,sizeof(int));

          
        vec[i].v1               = (int *)calloc(x,sizeof(int));
        vec[i].v2               = (int *)calloc(x,sizeof(int));
        vec[i].n_elem           = x;

       }
         
    vec[0].matriz =(int **)calloc(x,sizeof(int *));

    for(i=0;i<x;i++)
       {

        vec[0].matriz[i]           = (int *)calloc(x,sizeof(int ));
       }


    pthread_create(&hilo1,NULL,llenar_matriz,(void *)&mul_matrices);
    pthread_join(hilo1,NULL);
    //printf("HOLA");
    

    vec[0].num = 0;    
    for(i=0;i < vec -> n_elem ;i++)
       {
        for(j = 0;j < vec -> n_elem ; j++)
          {
             vec[i].v1[j] = mul_matrices.matrizA[i][j];
             vec[i].v2[j] = mul_matrices.matrizB[j][i];
             vec[i].fila_actual = i;
             
          }
       }

    //pthread_mutex_init(&vec->mutex, NULL);
    int h;   

  //printf("Creating %d children\n", n);
  //foo("parent");
  int aux=0;
  int estado;
  int datomenor1;
  int ll;
  double durationmax=0;



  //printf("hola\n");
  for(h=0;h<x;h++)
  {
    //printf("alooooooooo\n");

        
        pid_t pid=fork();
        //printf("\naca%d\n",i );
        if (pid==0) 
        // only execute this if child 
        {
          //printf("%d %d %desta es i,h,x = \n",i,h,x );
          


        }
        else{
          start_t = clock();
          //printf("soy padre:)\n" );
          multiplicar_filas(h,vec);
          datomenor1=x-1;
          //printf("acah %d\n",h );

          //printf("%d\n", );
          //pmem[1000]=50;
          int k=h*x;

          for (ll=0;ll<x;ll++){
            pmem[k] = vec[0].matriz[h][ll];
            //printf("Leído: %d", pmem[k]);
            m3[h][ll]= vec[0].matriz[h][ll];
            k++;
          }


          /*
          if (h==datomenor1){
            printf("\n-------------------------------------------");
            for(u=0;u < x ;u++)
               {
                printf("\n\t\t");
                for(j = 0;j < x; j++)
                   {
                  printf("[ %d ]",vec[0].matriz[u][j]);
                  m3[u][j]=vec[0].matriz[u][j];
                 }
            }

        }*/
        
            exit(0);
        }
        
        
        
        wait(&status); 
        //break;
        end_t = clock();

        duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        //printf("%f\n",duration );
        durationmax=durationmax+duration;
        // only the parent waits 
  }
  //printf("bye\n");
  //printf("alo\n");
  

  printf("%f\n",durationmax);

  //printf("Leído: %d", pmem[0]);


  /*
  for(j = 0;j < x*x; j++)
  {
    //pmem[j] = vec[0].matriz[u][j];
    printf("Leído: %d", pmem[j]);
  }*/

  //printf("acas%d\n",pmem[1000] );


/*
    printf("\n-------------------------------------------");
    for(u=0;u < x ;u++)
       {
        printf("\n\t\t");
        for(j = 0;j < x; j++)
           {
          printf("[ %d ]",m3[u][j]);
         }
    }*/

    shmdt((int *)id); //Desconecta el segmento de memoria compartida
    shmctl(id,IPC_RMID,0); //Elimina el segmento de memoria compartida
    printf("\n");
    

    for (i = 0;i < x;i++)
     {
      free(mul_matrices.matrizA[i]);
      free(mul_matrices.matrizB[i]);
      free(vec[i].matriz);
      //free(vec[i].matriz[i]);
      free(vec[i].v1);
      free(vec[i].v2);
     }
    
    
    //free(vec.matriz);
    free(mul_matrices.matrizA);
    free(mul_matrices.matrizB);
    free(vec);  
    pthread_exit(NULL);
  exit(0);
 	return 0;



}
