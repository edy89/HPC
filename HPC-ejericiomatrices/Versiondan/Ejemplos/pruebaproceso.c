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
/*  
int main() 
{ 
	for(int i=0;i<7;i++) // loop will run n times (n=5) 
	{ 
		if(fork() == 0) 
		{ 
			printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
			exit(0); 
		} 
		else{
			printf("DAD%d", getppid());
		}
	} 
	//for(int i=0;i<5;i++) // loop will run n times (n=5) 
	wait(NULL); 
	
} 

  

void forkexample() 
{ 
    int x = 1; 
  
    if (fork() == 0) 
        printf("Child has x = %d\n", ++x); 
    else
        printf("Parent has x = %d\n", --x); 
} 
int main() 
{ 
    forkexample(); 
    return 0; 
} 
*/
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
  
    //printf("\n");
    
}

void multiplicar_filas(int contador,void *args)
{
  vector *v = (vector *)args;  
  int i,j,k,aux,aux2,estado,num;
  printf("alo %d%d",contador,v[contador].fila_actual);

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
       printf("DATO %d \n",v[i].v1[j]);
       printf("DATO %d \n",v[k].v2[j]); 
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
      printf("[%d]\n", aux);
      aux = 0;

    }
    //v[0].num=v[0].num+1;
  }


  //pthread_mutex_unlock(&v->mutex);
  //printf("ADIOS");

      
}
/*
int foo(const char *whoami)
{
        printf("I am a %s.  My pid is:%d  my ppid is %d\n",
                        whoami, getpid(), getppid() );
        return 1;
}

int main(void)
{
        int n= 10;
        int i=0;
        int status=0;

        int x = 5;

        //printf("Creating %d children\n", n);
        //foo("parent");
        for(i=0;i<n;i++)
        {
                pid_t pid=fork();
                printf("aca%d\n",i );
                if (pid==0) 
                {
                    //foo("child");
                    for(i=0; i< 5; i++)

                    {
                		printf("bro%d\n",i );
                        x++;
                        printf("x value in for: %d \n", x);
                    }

                    exit(0);

                }
                wait(&status);  
        }

        x = 100 * x;
        printf("x value in main: %d ", x);


        return 0;
}
*/

/*
int main()
{
  int child;
  //int *number = (int*)malloc(sizeof(int));
  int *number = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  int i;

  *number = 10;

  child = fork();

  if (child==-1)
    {
      exit(1);
    }
  else if (child==0)
    {
      for (i=0; i<10; ++i)
    {
      usleep(100);
      printf ("CHILD -- Number: %d\n", *number);
      *number=i;
    }
      exit(0);
    }
  else
    {
      for (i=20; i<30; ++i)
    {
      usleep(100);
      printf ("MAIN -- Number: %d\n", *number);
      *number=i;
    }
    }
  wait(NULL);
  printf("%daca\n", *number);
  //free(number);
  munmap(number, sizeof(int));

}

*/
pid_t pid;
key_t clave;	//Clave de acceso a la zona de memoria
long int id;	//Identificador de la zona de memoria
int *pmem=NULL;	//Puntero a la zona de memoria

int main(int argc, char *argv[]) {

	//Creamos un área de memoria compartida
	clave=ftok("/bin/ls",33); //Cualquier fichero existente y cualquier int
	id=shmget(clave,sizeof(int)*100,0777|IPC_CREAT);
	pmem=(int *)shmat(id,(char *)0,0);
	
	pid = fork();
	if (pid == 0){
		//Soy el proceso hijo
		pmem[5] = 17; //Escribo en la memoria
	}
	else{
		//Soy el proceso padre
		usleep(100);
		printf("Leído: %d", pmem[5]);
		shmdt((char *)id); //Desconecta el segmento de memoria compartida
		shmctl(id,IPC_RMID,0); //Elimina el segmento de memoria compartida
	}
}
