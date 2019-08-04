#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# include <string.h>
#include <curand.h>
#include <cuda_runtime.h>


__global__ void mover_autos(int *d_A, int *d_B, int x)
{
/*	int a=0;
	int b=0;
	int x1=0;
	int y1=0;
	int u=0;*/
	int i = threadIdx.x;


	if (i < x)
	{
		d_B[i] = 3;

/*		a=d_A[i];
		b=d_A[i+1];
		if 	   (a==0 && b==0){x1=0;y1=0;u=0;}
			else if(a==0 && b==1){x1=0;y1=1;u=0;}
			else if(a==1 && b==0){x1=0;y1=1;u=1;}
			else if(a==1 && b==1){x1=1;y1=1;u=0;}

	 		if (u==1)
	 		{
	 			d_B[i] = x1;
	 			d_B[i+1] = y1;	
	 			i++;
	 		}
	 		else{
	 			d_B[i]=x1;
	 			d_B[i+1]=y1;
	 		}*/
	}			 
		
/*	int a1,b1;
	a=d_A[x-1];
	b=d_A[0];
	if 	   (a==0 && b==0){a1=0;b1=0;u=0;}
	else if(a==0 && b==1){a1=0;b1=1;u=0;}
	else if(a==1 && b==0){a1=0;b1=1;u=1;}
	else if(a==1 && b==1){a1=1;b1=1;u=0;}

	if(u==1)
	{
		d_B[x-1]=a1;
		d_B[0]=b1;					//guardamos los resultados en el result
	}*/
}


int main(int argc, char *argv[])
{
	
    clock_t start_t, end_t;
    double duration;
    srand (time(NULL));

    
    int parametro,x;
    parametro = atoi(argv[1]);
    x = parametro;


	int p,cantidadinter;
    p = atoi(argv[2]);
    cantidadinter = p;
    //printf("%d\n", cantidadinter);

    size_t nBytes = x * sizeof(int);

	int* h_A = (int*)malloc(nBytes);
	int* h_B = (int*)malloc(nBytes);
	//int* h_C = (int*)malloc(nBytes);

	//int dev = 0;
    //cudaSetDevice(dev);

	// declare device vectors in the device (GPU) memory
	int *d_A,*d_B;//*d_C;

	for(int i = 0;i < x ; i++)
	 {
		h_A[i] = 1;
		//printf("[%d]", h_A[i]);
     } 

	printf("\n");

    cudaMalloc((int **)&d_A, nBytes);
    cudaMalloc((int **)&d_B, nBytes);

	cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice);

	for (int i = 0; i < x; ++i)
	{
		printf("%d\n", h_A[i]);
		printf("%d\n", d_A[i]);
	}

	start_t = clock();

	for(int k=1;k<cantidadinter;k++)
	{
	  mover_autos <<<1, 4>>> (d_A, d_B, 4);
 	}

 	cudaMemcpy(h_A, d_A, nBytes, cudaMemcpyDeviceToHost);
	cudaMemcpy(h_B, d_B, nBytes, cudaMemcpyDeviceToHost);


    end_t = clock();
    duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEL tiempo fue: %f",duration);
    cudaFree(d_A);
  	cudaFree(d_B);

	free (h_A);
	free(h_B);

	return cudaDeviceReset();
	//return 0;
}