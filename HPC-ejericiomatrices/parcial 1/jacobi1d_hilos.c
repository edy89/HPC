#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <pthread.h>
# include <unistd.h>
#include "timing.h"
//gcc -DUSE_CLOCK -O3 jacobi1d_hilos.c timing.c -o jacobi1dhilos -lpthread
//jacobi1dhilos 100 1000 u_serial.out > timing_serial.out
/* --
 * Do nsweeps sweeps of Jacobi iteration on a 1D Poisson problem
 * 
 *    -u'' = f
 *
 * discretized by n+1 equally spaced mesh points on [0,1].
 * u is subject to Dirichlet boundary conditions specified in
 * the u[0] and u[n] entries of the initial vector.
 */
/*
void jacobi(int nsweeps, int n, double* u, double* f)
{
    int i, sweep;
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp = (double*) malloc( (n+1) * sizeof(double) );

    /* Fill boundary conditions into utmp */
    /*utmp[0] = u[0];
    utmp[n] = u[n];

    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        
        /* Old data in u; new data in utmp */
        /*for (i = 1; i < n; ++i)
            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2; 
        
        /* Old data in utmp; new data in u */
        /*for (i = 1; i < n; ++i)
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
    }

    free(utmp);
}
*/

typedef struct 
{
  int nsteps,n;
  double *u,*f,*aux;
  //pthread_mutex_t mutex;  
}pack_jacobi;

void *jacobi_values(void *args)
{
    pack_jacobi *j = (pack_jacobi *) args;
    //double* aux = (double*) malloc( (n+1) * sizeof(double) );
    int i;
    //pthread_mutex_lock(&j->mutex);
    //printf("%s\n", "entre a jacobi values");
    //printf("%f\n", j->f[0]);
    printf("%s %d\n", "Yo soy n: ",j->n);

    /*for(i = 1; i<j->n; ++i)
        j->aux[i] = (j->u[i - 1] + j->u[i + 1] + ((1.0/j->n) * (1.0/j->n)) * j->f[i]) / 2;
      */  

    free(j->aux);
    //pthread_mutex_unlock(&j->mutex);
}

void *jacobi_values2(void *args)
{
    pack_jacobi *j = (pack_jacobi *) args;
    printf("%s\n", "entre a jacobi values 2");
    //double* aux = (double*) malloc( (n+1) * sizeof(double) );

    int i;

    for(i = 1; i<j->n; ++i)
        j->u[i] = (j->aux[i - 1] + j->aux[i + 1] + ((1.0/j->n) * (1.0/j->n)) * j->f[i]) / 2;

    free(j->aux);
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
    int i;
    //int n, nsteps;
    //double* u;
    //double* f;
    double h;
    timing_t tstart, tend;
    //char* fname;
    pack_jacobi *pack;

    pthread_t hilo,hilo2;
    /* Process arguments */
    /*n      = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname  = (argc > 3) ? argv[3] : NULL;
    h      = 1.0/n;*/

    pack = (pack_jacobi *) malloc(sizeof(pack_jacobi));

    pack->n      = (argc > 1) ? atoi(argv[1]) : 100;
    pack->nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    //h            = 1.0 / (pack -> n);
    //fname  = (argc > 3) ? argv[3] : NULL;

    /* Allocate and initialize arrays */
    pack->u   = (double*) malloc(((pack -> n) + 1) * sizeof(double) );
    pack->f   = (double*) malloc(((pack -> n) + 1) * sizeof(double) );
    pack->aux = (double*) malloc(((pack -> n) + 1) * sizeof(double) );

    memset(pack->u, 0, (pack->n + 1) * sizeof(double));

    
    //pthread_mutex_init(&pack -> mutex, NULL);
    
    for (i = 0; i <= pack->n; ++i)
        {
          pack->f[i] = i * (1.0 / (pack -> n));
          printf("%f\n", pack -> f[i]);
        }

    //printf("%s %f\n","Yo soy n: ", pack->n);
    /* Run the solver */
    get_time(&tstart);
    printf("%s %d\n", "Yo soy n: ",pack->n);
    pthread_create(&hilo,NULL,jacobi_values,(void *)&pack);
    pthread_join(hilo,NULL);

    //pthread_create(&hilo2,NULL,jacobi_values2,(void *)&pack);
    //pthread_join(hilo2,NULL);
    //jacobi_values(pack.n, pack.u, f);
    get_time(&tend);

    /* Run the solver */    
   /* printf("n: %d\n"
           "nsteps: %d\n"
           "Elapsed time: %g s\n", 
           pack->n, pack->nsteps, timespec_diff(tstart, tend));*/

    /* Write the results */
    /*if (fname)
        write_solution(pack->n, pack->u, fname);*/

    free(pack->f);
    free(pack->u);
    free(pack);
    //pthread_exit(NULL);
    return 0;
}
