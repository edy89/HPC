#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timing.h"
#include <pthread.h>

/* --
 * Do nsweeps sweeps of Jacobi iteration on a 1D Poisson problem
 * 
 *    -u'' = f
 *
 * discretized by n+1 equally spaced mesh points on [0,1].
 * u is subject to Dirichlet boundary conditions specified in
 * the u[0] and u[n] entries of the initial vector.

gcc -DUSE_CLOCK -O3 hilo4.c -o fin4 -lpthread
 ./fin4 1000 10 u_serial4.out > timing_serial.out
 */

struct vectores{
  int n,nsteps,num;
  double *v1,*v2,*utmp;
  double *answer;

  pthread_mutex_t mutex;

};
typedef struct _thread_data_t {
  int tid;
  double stuff;
  int n,nsteps,num;
  double *v1,*v2,*utmp;
  double *answer;
} thread_data_t;
 
/* thread function */
void *thr_func(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    //printf("hello from thr_func, thread id: %d\n", data->tid);
    

    double *u;
    double *f;
    double *utmp;
    int i,nsweeps;

    double h  = 1.0 / data->n;
    double h2 = h*h;

    u=data->v1;
    f=data->v2;
    utmp=data->utmp;
    i=data->tid;
        
    utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;

    //printf("%f\n",utmp[i]);
    

    pthread_exit(NULL);
}


void *thr_func2(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    //printf("hello from thr_func, thread id: %d\n", data->tid);
    

    double *u;
    double *f;
    double *utmp;
    int i,nsweeps;

    double h  = 1.0 / data->n;
    double h2 = h*h;

    u=data->v1;
    f=data->v2;
    utmp=data->utmp;
    i=data->tid;
        
    u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;

    //printf("%f\n",utmp[i]);
    
    pthread_exit(NULL);
}


void* diva(void* arg)
{
    
    /*struct vectores *arg_struct =(struct vectores*) arg;

    double *u;
    double *f;
    double *utmp;
    int i,nsweeps;

    double h  = 1.0 / arg_struct->n;
    double h2 = h*h;

    u=arg_struct->v1;
    f=arg_struct->v2;
    utmp=arg_struct->utmp;
    i=arg_struct->num;
        
    utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
    pthread_exit(0);*/
    
}


void jacobi(int nsweeps, int n, double* u, double* f)
{
    int i, sweep,k;
    double h  = 1.0 / n;
    double h2 = h*h;
    /* Fill boundary conditions into utmp */
    struct vectores vec1;
    pthread_t tids[n];
    // Launch thread
    vec1.v1  = (double*) malloc( (n+1) * sizeof(double) );
    vec1.v2  = (double*) malloc( (n+1) * sizeof(double) );
    vec1.utmp = (double*) malloc( (n+1) * sizeof(double) );
    vec1.v2=f;
    vec1.v1=u;
    vec1.utmp[0] = u[0];
    vec1.utmp[n] = u[n];
    vec1.n=n;
    vec1.nsteps=nsweeps;
    double *aux;

    pthread_t thr[n+1];
    int rc;
    /* create a thread_data_t argument array */
    thread_data_t thr_data[n+1];


    /* create threads */

    for (i = 1; i < n; i++){
        
        thr_data[i].utmp = (double*) malloc( (n+1) * sizeof(double) );
    }


    for (i = 1; i < n; i++){
        //printf("HOLI\n");
        thr_data[i].v2=f;
        thr_data[i].v1=u;
        thr_data[i].utmp[0] = u[0];
        thr_data[i].utmp[n] = u[n];
        thr_data[i].n=n;
        thr_data[i].nsteps=nsweeps;

    }

    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        /* Old data in u; new data in utmp */
        
        for (i = 1; i < n; i++){
            //utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
 
            thr_data[i].tid = i;

            if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
              fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            }
            
        }
        

        for (i = 1; i < n; ++i) {
            pthread_join(thr[i], NULL);
            vec1.utmp[i]=thr_data[i].utmp[i];   
            }
        
        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i){            
            u[i] = (vec1.utmp[i-1] + vec1.utmp[i+1] + h2*f[i])/2;
            }

        for (i = 1; i < n; i++){
            thr_data[i].v1=u;
        }

    }
    


    free(vec1.utmp);

    for (i = 1; i < n; i++){
        
        free(thr_data[i].utmp);
    }


    

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
    int n, nsteps;
    double* u;
    double* f;
    double h;
    timing_t tstart, tend;
    char* fname;

    /* Process arguments */
    n      = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname  = (argc > 3) ? argv[3] : NULL;
    h      = 1.0/n;

    /* Allocate and initialize arrays */
    u = (double*) malloc( (n+1) * sizeof(double) );
    f = (double*) malloc( (n+1) * sizeof(double) );

    memset(u, 0, (n+1) * sizeof(double));
    
    for (i = 0; i <= n; ++i)
        f[i] = i * h;

    int  sweep,nsweeps,k;
    double h2 = h*h;
    /* Fill boundary conditions into utmp */
    struct vectores vec1;
    // Launch thread
    nsweeps=nsteps;
    vec1.v1  = (double*) malloc( (n+1) * sizeof(double) );
    vec1.v2  = (double*) malloc( (n+1) * sizeof(double) );
    vec1.utmp = (double*) malloc( (n+1) * sizeof(double) );
    vec1.v2=f;
    vec1.v1=u;
    vec1.utmp[0] = u[0];
    vec1.utmp[n] = u[n];
    vec1.n=n;
    vec1.nsteps=nsweeps;

    pthread_t thr[n+1];
    int rc,j;
    /* create a thread_data_t argument array */
    thread_data_t thr_data[n+1];


    for (i = 1; i < n; i++){
        
        thr_data[i].utmp = (double*) malloc( (n+1) * sizeof(double) );
    }


    for (i = 1; i < n; i++){
        //printf("HOLI\n");
        thr_data[i].v2=f;
        thr_data[i].v1=u;
        thr_data[i].utmp[0] = u[0];
        thr_data[i].utmp[n] = u[n];
        thr_data[i].n=n;
        thr_data[i].nsteps=nsweeps;

    }

    /* Run the solver */
    //jacobi(nsteps, n, u, f);

    get_time(&tstart);

    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        /* Old data in u; new data in utmp */
        
        for (i = 1; i < n; i++){
            //utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
 
            thr_data[i].tid = i;

            if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
              fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            }
            
        }
        

        for (i = 1; i < n; ++i) {
            pthread_join(thr[i], NULL);
            vec1.utmp[i]=thr_data[i].utmp[i];   
            }


        for (int i = 1; i < n; ++i)
            {
            thr_data[i].utmp=vec1.utmp;                
            }    
        
        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i){            
            //u[i] = (vec1.utmp[i-1] + vec1.utmp[i+1] + h2*f[i])/2;
            
            thr_data[i].tid = i;

            if ((rc = pthread_create(&thr[i], NULL, thr_func2, &thr_data[i]))) {
              fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            }
            }
        for (i = 1; i < n; ++i) {
            pthread_join(thr[i], NULL);
            vec1.v1[i]=thr_data[i].v1[i];   
            }    
        for (i = 1; i < n; i++){
            thr_data[i].v1=vec1.v1;
        }

    }
    get_time(&tend);

    //for (int i=0;i<n;i++){
    //    printf("%f\n",u[i] );
    //    printf("%f\n",f[i] );
    //}

    /* Run the solver */    
    /* Run the solver */    
    printf("n: %d\n"
           "nsteps: %d\n"
           "Elapsed time: %g s\n", 
           n, nsteps, timespec_diff(tstart, tend));
    
    /* Write the results */
    if (fname)
        write_solution(n, u, fname);

    free(vec1.utmp);

    for (i = 1; i < n; i++){
        
        free(thr_data[i].utmp);
    }


    free(f);
    free(u);
    return 0;
}
