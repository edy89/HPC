#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

typedef struct 
{
  int *V,*N,dimension;
  //char id;
}pack_matrices;



void *llenar_matriz(void *args)
{
  pack_matrices  *m = (pack_matrices *)args;
  int i,j,x;
  

	for(i = 0;i < m -> dimension ; i++)
	   {
	    m -> V[i] = rand() % 2;
	 }

	 
    
    for(i = 0;i < m -> dimension; i++)
       {
      printf("[ %d ]", m -> V[i]);
     }
    

}




int casos(int a, int b){
	int x,y;
	if 	   (a==0 && b==0){x=0;y=0;}
	else if(a==0 && b==1){x=0;y=1;}
	else if(a==1 && b==0){x=0;y=1;}
	else if(a==1 && b==1){x=1;y=1;}
	return x,y;
}

void  funcion(void *args){

  pack_matrices  *m = (pack_matrices *)args;
  int i,j,x;
  


} 





int main(int argc, char *argv[])
{

    int i,j,k;

    clock_t start_t, end_t;
    double duration;
    srand (time(NULL));
    
    int parametro,x;
    parametro=atoi(argv[1]);
    x=parametro;


	int p,cantidadinter;
    p=atoi(argv[2]);
    cantidadinter=p;
    printf("%d\n", cantidadinter);


   
    pack_matrices mul_matrices;
    mul_matrices.dimension = x;

    mul_matrices.V = (int *)calloc(x,sizeof(int ));
    mul_matrices.N = (int *)calloc(x,sizeof(int ));


    

   	llenar_matriz(&mul_matrices);



	int modulo;
	modulo=x/3;

	start_t = clock();
	for(int k=1;k<cantidadinter;k++){

		
	//mod=n/3 								//partimos para los hilos o mpi (3 como condición inicial)

	

		int a=0;
		int b=0;
		int x1=0;
		int y1=0;
		int u=0;
		int entrada;
		int entrada2;

		for(int i=0;i<x-1;i++){

			if(i==0){
				entrada=1;
				entrada2=1;
			}	
			else{
				entrada=mul_matrices.V[i-1];
				entrada2=mul_matrices.V[i];


			}

			if ( entrada==1 && entrada2==0)
			{
				
			}
			else{

				a=mul_matrices.V[i];
				b=mul_matrices.V[i+1];
				if 	   (a==0 && b==0){x1=0;y1=0;u=0;}
				else if(a==0 && b==1){x1=0;y1=1;u=0;}
				else if(a==1 && b==0){x1=0;y1=1;u=1;}
				else if(a==1 && b==1){x1=1;y1=1;u=0;}

		 		if (u==1)
		 		{
		 			mul_matrices.N[i]=x1;
		 			mul_matrices.N[i+1]=y1;
		 			
		 		}
		 		else{
		 			mul_matrices.N[i]=x1;
		 			mul_matrices.N[i+1]=y1;
			 			
			 
		 		}


			}


			 
		}
		

		int a1,b1;
		a=mul_matrices.V[x-1];
		b=mul_matrices.V[0];
		if 	   (a==0 && b==0){a1=0;b1=0;u=0;}
		else if(a==0 && b==1){a1=0;b1=1;u=0;}
		else if(a==1 && b==0){a1=0;b1=1;u=1;}
		else if(a==1 && b==1){a1=1;b1=1;u=0;}

		if(u==1){
			mul_matrices.N[x-1]=a1;
			mul_matrices.N[0]=b1;					//guardamos los resultados en el result
		}
		


		for(i = 0;i < mul_matrices.dimension ; i++)
		{
		  	mul_matrices.V[i] = mul_matrices.N[i];
		} 



		printf("\nMATRIZ resultado\n" );
	    for(i = 0;i < mul_matrices.dimension; i++)
	       {
	      printf("[ %d ]", mul_matrices.V[i]);
	     }

 	}

    end_t = clock();
    duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEL tiempo fue: %f",duration);

	printf("\n" );

    free(mul_matrices.N);
    free(mul_matrices.V);

}