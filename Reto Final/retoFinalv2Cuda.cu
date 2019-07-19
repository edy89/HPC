#include <cuda_runtime.h>
#include <stdio.h>

void initialData(int *ip, int size)
{
    srand (time(NULL));

    for (int i = 0; i < size; i++)
    {
        ip[i] = rand() % 2;
    }

    return;
}

__global__ void movimientoAutos(int *d_A, int *d_B, const int N)
{
    int a=0;
    int b=0;
    int x1=0;
    int y1=0;
    int u=0;
    int entrada;
    int entrada2;
    int i = threadIdx.x;

    if (i < N)
    {

        if(i==0){
                entrada  = 1;
                entrada2 = 1;
            }   
            else{
                entrada  = d_A[i-1];
                entrada2 = d_A[i];


            }

            if ( entrada==1 && entrada2==0)
             {
               d_B[i-1] = 0;
               d_B[i] = 1;
             }
            else{

                a = d_A[i];
                b = d_A[i+1];
                if     (a==0 && b==0){x1=0;y1=0;u=0;}
                else if(a==0 && b==1){x1=0;y1=1;u=0;}
                else if(a==1 && b==0){x1=0;y1=1;u=1;}
                else if(a==1 && b==1){x1=1;y1=1;u=0;}

                if (u==1)
                {
                    d_B[i]   = x1;
                    d_B[i+1] = y1;
                    
                }
                else{
                    d_B[i]   = x1;
                    d_B[i+1] = y1;
                        
             
                }


            }
    }            
        
}


int main(int argc, char **argv)
{
    printf("%s Starting...\n", argv[0]);
    clock_t start_t, end_t;
    double duration;

    int parametro,x;
    parametro = atoi(argv[1]);
    x = parametro;


    int p,cantidadinter;
    p = atoi(argv[2]);
    cantidadinter = p;

    int dev = 0;
    cudaSetDevice(dev);

    int nElem = x;
    printf("Vector size %d\n", nElem);

    size_t nBytes = nElem * sizeof(int);

    int *h_A, *h_B, *gpuRef;
    h_A     = (int *)malloc(nBytes);
    h_B     = (int *)malloc(nBytes);
    gpuRef  = (int *)malloc(nBytes);

    initialData(h_A, nElem);
/*    for (int i = 0; i < nElem; ++i)
    {
        printf("[%d]", h_A[i]);
    }*/


    memset(gpuRef,  0, nBytes);
    memset(h_B,  0, nBytes);


    int *d_A, *d_B; //*d_C;
    cudaMalloc((int**)&d_A, nBytes);
    cudaMalloc((int**)&d_B, nBytes);



    cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice);


    dim3 block (nElem);
    dim3 grid  (1);

    start_t = clock();
    for (int i = 0; i < cantidadinter; ++i)
    {
        movimientoAutos<<<grid, block>>>(d_A, d_B, nElem);       
        //printf("\nExecution configure <<<%d, %d>>>\n", grid.x, block.x);

        cudaMemcpy(h_B, d_B, nBytes, cudaMemcpyDeviceToHost);
        cudaMemcpy(h_A, d_A, nBytes, cudaMemcpyDeviceToHost);
        int a=0;
        int b=0;
        int u=0;
        int a1,b1;
        
        a=h_A[x-1];
        b=h_A[0];

        if     (a==0 && b==0){a1=0;b1=0;u=0;}
        else if(a==0 && b==1){a1=0;b1=1;u=0;}
        else if(a==1 && b==0){a1=0;b1=1;u=1;}
        else if(a==1 && b==1){a1=1;b1=1;u=0;}

        if(u==1)
        {
            h_B[x-1] = a1;
            h_B[0]   = b1;                  //guardamos los resultados en el result
        }

/*        for (int i = 0; i < nElem; ++i)
        {
           h_A[i] = h_B[i];
           printf("[%d]", h_B[i]);
        }

        printf("\n");*/

        cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
        cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice);
    }
    end_t = clock();
    duration = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nEL tiempo fue: %f\n",duration);

/*    printf("----------------------\n");

    for (int i = 0; i < nElem; ++i)
    {
        printf("[%d]",h_B[i]);
    }

    printf("\n");*/

    cudaFree(d_A);
    cudaFree(d_B);


    free(h_A);
    free(h_B);
    free(gpuRef);

    cudaDeviceReset();
    return(0);
}
