#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "timing.h"
//cd /media/edison/5CAC40DEAC40B3F4/Users/Edyson/Desktop/HPC/Parcial1/parcial\ 1
//gcc -DUSE_CLOCK -O3 jacobi1d_hilos.c timing.c -o jacobi1dhilos -lpthread
//jacobi1dhilos 100 1000 u_serial.out > timing_serial.out

typedef struct 
{
  int nsteps,n;
  double *u,*f,*aux;
  //pthread_mutex_t mutex;  
}pack_jacobi;

void *jacobi_values(void *args)
{
    pack_jacobi *j = (pack_jacobi *) args;
    int i;
    //pthread_mutex_lock(&j->mutex);
    j->aux[0] = j->u[0];
    j->aux[j->n] = j->u[j->n];
    
    for(i = 1; i<j->n; ++i)
        j->aux[i] = (j->u[i - 1] + j->u[i + 1] + ((1.0/j->n) * (1.0/j->n)) * j->f[i]) / 2;
        
    //pthread_mutex_unlock(&j->mutex);
}

void *jacobi_values2(void *args)
{
    pack_jacobi *j = (pack_jacobi *) args;
    int i;
	
    for(i = 1; i<j->n; ++i)
        j->u[i] = (j->aux[i - 1] + j->aux[i + 1] + ((1.0/j->n) * (1.0/j->n)) * j->f[i]) / 2;

    //pthread_mutex_destroy(&j -> mutex);
}


void write_solution(int n, double* u, const char* fname)
{
    int i;
    double h = 1.0 / n;
    FILE* fp = fopen(fname, "w+");
    for (i = 0; i <= n; ++i)
        fprintf(fp, "%g %g\n", i*h, u[i]);
    fclose(fp);
}


int main(int argc, char** argv)
{
    int i,sweep;
    double h;
    timing_t tstart, tend;
    char* fname;
    pack_jacobi *pack;

    pthread_t hilo,hilo2;

    pack = (pack_jacobi *) malloc(sizeof(pack_jacobi));

    pack->n      = (argc > 1) ? atoi(argv[1]) : 100;
    pack->nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname  = (argc > 3) ? argv[3] : NULL;

    /* Allocate and initialize arrays */
    pack->u   = (double*) malloc(((pack -> n) + 1) * sizeof(double) );
    pack->f   = (double*) malloc(((pack -> n) + 1) * sizeof(double) );
    pack->aux = (double*) malloc(((pack -> n) + 1) * sizeof(double) );

    memset(pack->u, 0, (pack->n + 1) * sizeof(double));

    
    //pthread_mutex_init(&pack -> mutex, NULL);
    
    for (i = 0; i <= pack->n; ++i)
        {
          pack->f[i] = i * (1.0 / (pack -> n));
          //printf("%f\n", pack -> f[i]);
        }

    /* Run the solver */
    get_time(&tstart);
    //for (sweep = 0; sweep < pack->nsteps; sweep += 2) 
    //{
        pthread_create(&hilo,NULL,jacobi_values,(void *)pack);
    	pthread_create(&hilo2,NULL,jacobi_values2,(void *)pack);
    //}
    get_time(&tend);
    
    pthread_join(hilo,NULL);
    pthread_join(hilo2,NULL);

    /* Run the solver */    
    /*printf("n: %d\n"
           "nsteps: %d\n"
           "Elapsed time: %g s\n", 
           pack->n, pack->nsteps, timespec_diff(tstart, tend));*/
           
    printf("%g\n",timespec_diff(tstart,tend));

    /* Write the results */
    if (fname)
        write_solution(pack->n, pack->u, fname);

    free(pack->f);
    free(pack->u);
    free(pack->aux);
    free(pack);
    //pthread_exit(NULL);
    return 0;
}
