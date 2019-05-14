#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timing.h"
#include <time.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
/* --
 * Do nsweeps sweeps of Jacobi iteration on a 1D Poisson problem
 * 
 *    -u'' = f
 *
 * discretized by n+1 equally spaced mesh points on [0,1].
 * u is subject to Dirichlet boundary conditions specified in
 * the u[0] and u[n] entries of the initial vector.
 */
struct sum_runner_struct {
    long long limit;
    long long answer;
};


struct vectores{
  int n,nsteps,num;
  double *v1,*v2,*utmp;
  double *answer;

  pthread_mutex_t mutex;

};


// Thread function to generate sum of 0 to N
void* sum_runner(void* arg)
{
    struct sum_runner_struct *arg_struct =(struct sum_runner_struct*) arg;

    long long sum = 0;
    for (long long i = 0; i <= arg_struct->limit; i++) {
        sum += i;
    }

    arg_struct->answer = sum;

    pthread_exit(0);
}


void* operacion(void* arg)
{
    struct vectores *arg_struct =(struct vectores*) arg;

    //long long sum = 0;
    //for (long long i = 0; i <= arg_struct->limit; i++) {
    //    sum += i;
    //}
    double *u;
    double *f;
    double *utmp;
    int nu;
    u=arg_struct->v1;
    f=arg_struct->v2;
    utmp=arg_struct->utmp;
    nu=arg_struct->num;
    //double h  = 1.0 / arg_struct.n;
    //double h2 = h*h;
    
    printf("%d\n", nu);

    //utmp = (u[i-1] + u[i+1] + h2*f[i])/2;



    //arg_struct->answer = utmp;



    pthread_exit(0);
}

void jacobi(int nsweeps, int n, double* u, double* f)
{
    int i, sweep;
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp = (double*) malloc( (n+1) * sizeof(double) );

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];


    struct sum_runner_struct args[n];
    struct vectores vec1;

    // Launch thread
    pthread_t tids[n];
    vec1.v1 = (double*) malloc( (n+1) * sizeof(double) );
    vec1.v2 = (double*) malloc( (n+1) * sizeof(double) );
    vec1.utmp = (double*) malloc( (n+1) * sizeof(double) );
    vec1.n=n;
    vec1.nsteps=nsweeps;
    vec1.v1=u;
    vec1.v2=f;
    vec1.utmp=utmp;
    vec1.utmp[0] = u[0];
    vec1.utmp[n] = u[n];



    /*
    for (int i = 0; i < n; i++) {
        //args[i].limit = atoll(argv[i + 1]);

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tids[i], &attr, sum_runner, &args[i]);
    }


    // Wait until thread is done its work
    for (int i = 0; i < num_args; i++) {
        pthread_join(tids[i], NULL);
        printf("Sum for thread %d is %lld\n",
                i, args[i].answer);
    }
    */

    //for (sweep = 0; sweep < nsweeps; sweep += 2) {
        
        /* Old data in u; new data in utmp */



        for (i = 1; i < n; i+=2){

            int cont=i+2;
            vec1.num=i; 
            for(int h=i;h<cont;h++){
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_create(&tids[h], &attr, operacion, &vec1);
            }
            for (int j = i; j < cont; j++) 
            {
                pthread_join(tids[j], NULL);

                //printf("Sum for thread %d is %lld\n",i, args[i].answer);
            }   
            //vec1[0].utmp[i]=vec1[i].utmp[i];
            //vec1[0].utmp[i+1]=vec1[i+1].utmp[i];
        }
                
        
        /* Old data in utmp; new data in u */
        //for (i = 1; i < n; ++i)
        //    u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;

    

    free(utmp);
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
    //get_time(&tstart);
    jacobi(nsteps, n, u, f);
    //get_time(&tend);

    /* Run the solver */    
    //printf("n: %d\n""nsteps: %d\n""Elapsed time: %g s\n", n, nsteps, timespec_diff(tstart, tend));

    /* Write the results */
    //if (fname)
    //    write_solution(n, u, fname);

    free(f);
    free(u);
    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timing.h"

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
  double *answer;

  pthread_mutex_t mutex;

};


void* div(void* arg)
{
    double *u;
    double *f;
    double *utmp;
    int nu,nsweeps;

    double h  = 1.0 / arg_struct->n;
    double h2 = h*h;

    u=arg_struct->v1;
    f=arg_struct->v2;
    utmp=arg_struct->utmp;

    nsweeps=arg_struct->nsteps;
    int mitad=nsweeps/2;

    for (sweep = 0; sweep < mitad; sweep += 2) {
        
        /* Old data in u; new data in utmp */
        for (i = 1; i < n; ++i)
            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;

        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
    }

    pthread_exit(0);
}

void* div2(void* arg)
{
    struct vectores *arg_struct =(struct vectores*) arg;


    double h  = 1.0 / arg_struct->n;
    double h2 = h*h;

    double *u;
    double *f;
    double *utmp;
    int nu,nsweeps;
    u=arg_struct->v1;
    f=arg_struct->v2;
    utmp=arg_struct->utmp;

    nsweeps=arg_struct->nsteps;
    int mitad=nsweeps/2;

    for (k = mitad; k < nsweeps; k += 2) {
        
        /* Old data in u; new data in utmp */
        for (i = 1; i < n; ++i)
            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
        
        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
    }
    

    pthread_exit(0);
}
void jacobi(int nsweeps, int n, double* u, double* f)
{
    int i, sweep,k;
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp = (double*) malloc( (n+1) * sizeof(double) );

    double* utmp2 = (double*) malloc( (n+1) * sizeof(double) );
    /* Fill boundary conditions into utmp */

    int halfn=n/2;



    struct vectores vec1;

    // Launch thread
    pthread_t tids[2];
    vec1.v1 = (double*) malloc( (n+1) * sizeof(double) );
    vec1.v2 = (double*) malloc( (n+1) * sizeof(double) );
    vec1.utmp = (double*) malloc( (n+1) * sizeof(double) );
    vec1.n=n;
    vec1.nsteps=nsweeps;
    vec1.v1=u;
    vec1.v2=f;
    vec1.utmp=utmp;
    vec1.utmp[0] = u[0];
    vec1.utmp[n] = u[n];


    utmp[0] = u[0];
    utmp[n] = u[n];


    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tids[0], &attr, div, &vec1);
    pthread_create(&tids[1], &attr, div2, &vec1);



    free(utmp);
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

    for (int i=0;i<n;i++){
        printf("%f\n",u[i] );
        printf("%f\n",f[i] );
    }

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
