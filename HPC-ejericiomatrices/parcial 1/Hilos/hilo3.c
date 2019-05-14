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
 */

struct vectores{
  int n,nsteps,num;
  double *v1,*v2,*utmp;

  pthread_mutex_t mutex;

};


void* diva(void* arg)
{
    int n;    
    struct vectores *arg_struct =(struct vectores*) arg;
    n=arg_struct->n;
    double *u  = (double*) malloc( (n+1) * sizeof(double) );
    double *f  = (double*) malloc( (n+1) * sizeof(double) );
    double *utmp  = (double*) malloc( (n+1) * sizeof(double) );
    int i,nsweeps;

    double h  = 1.0 / arg_struct->n;
    double h2 = h*h;

    u=arg_struct->v1;
    f=arg_struct->v2;
    utmp=arg_struct->utmp;
    i=arg_struct->num;
        
    utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;


    pthread_exit(0);
    
}

void* diva2(void* arg)
{
    int n,i,nsweeps;
    struct vectores *arg_struct =(struct vectores*) arg;
    n=arg_struct->n;
    double *u  = (double*) malloc( (n+1) * sizeof(double) );
    double *f  = (double*) malloc( (n+1) * sizeof(double) );
    double *utmp  = (double*) malloc( (n+1) * sizeof(double) );
   
    double h  = 1.0 / n;
    double h2 = h*h;
    u=arg_struct->v1;
    f=arg_struct->v2;
    utmp=arg_struct->utmp;
    i=arg_struct->num;
     
    utmp[i+1] = (u[i] + u[i+2] + h2*f[i+1])/2;


  

    pthread_exit(0);
}


void jacobi(int nsweeps, int n, double* u, double* f)
{
    int i, sweep,k;
    double h  = 1.0 / n;
    double h2 = h*h;

    /* Fill boundary conditions into utmp */

    

    struct vectores vec1;

    pthread_t tids2[n];
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


    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        /* Old data in u; new data in utmp */
        
        for (i = 1; i < n; i+=2){
            //vec1.utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
            
            vec1.num=i;
            //pthread_attr_t attr;
            //pthread_attr_init(&attr);
            pthread_create(&tids2[i], NULL, diva, &vec1);
            pthread_create(&tids2[i+1], NULL, diva2, &vec1);

            pthread_join(tids2[i], NULL);
            pthread_join(tids2[i+1], NULL);


            
        }

        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
            u[i] = (vec1.utmp[i-1] + vec1.utmp[i+1] + h2*f[i])/2;
    }
    

    free(vec1.utmp);
    //pthread_exit(NULL);
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

    /* Run the solver */
    get_time(&tstart);
    jacobi(nsteps, n, u, f);
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

    free(f);
    free(u);

    
    return 0;
}
