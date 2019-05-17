
#include <string.h>

#include "timing.h"
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<linux/unistd.h>
#include<sys/syscall.h>
/* --
 * Do nsweeps sweeps of Jacobi iteration on a 1D Poisson problem
 * 
 *    -u'' = f
 *
 * discretized by n+1 equally spaced mesh points on [0,1].
 * u is subject to Dirichlet boundary conditions specified in
 * the u[0] and u[n] entries of the initial vector.
0 0
0.0001 1e-12
0.0002 2e-12
0.0003 3e-12
0.0004 4e-12
0.0005 5e-12
0.0006 6e-12
0.0007 7e-12
0.0008 8e-12
0.0009 9e-12

0.998 4.99e-08
0.9981 4.9905e-08
0.9982 4.991e-08
0.9983 4.9915e-08
0.9984 4.992e-08
0.9985 4.9925e-08
0.9986 4.993e-08
0.9987 4.9935e-08
0.9988 4.994e-08
0.9989 4.9945e-08
0.999 4.995e-08
0.9991 4.99452e-08
0.9992 4.99209e-08
0.9993 4.97795e-08
0.9994 4.94231e-08
0.9995 4.84125e-08
0.9996 4.63081e-08
0.9997 4.19381e-08
0.9998 3.41306e-08
0.9999 2.08348e-08
1 0


 */
struct vectores{
  int n,nsteps;
  double *v1,*v2,*utmp;

  pthread_mutex_t mutex;

};

void *jaco(void * args){

    struct vectores m = args;
    //double h  = 1.0 / n;
    //double h2 = h*h;

    printf("The id of %s is %u\n",(char*)ptr,syscall( __NR_gettid ));
    printf("The id of %s is %u\n",(char*)ptr,(unsigned int)pthread_self());
    //utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;

    /* Old data in u; new data in utmp */
    //for (i = 1; i < n; ++i)
    //    utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
    
    /* Old data in utmp; new data in u */
    //for (i = 1; i < n; ++i)
    //    u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;




}


void jacobi(int nsweeps, int n, double* u, double* f)
{
    int sweep;
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp = (double*) malloc( (n+1) * sizeof(double) );

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];
    int k;
    /*for(k=0;k<n+1;k++)
        printf("aca%f\n",u[k] );
    */
    pthread_t hilo;
    struct vectores vec1;
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
    for(k=0;k<n+1;k++)
        printf("aca%f\n",vec1.v2[k] );
    */

    int rc, i, j, detachstate;
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);





    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        
       
        //pthread_create(&hilo,NULL,jaco,(void *)vec1);


        /* Old data in u; new data in utmp */
        for (i = 1; i < n; ++i)
            //pthread_create(&hilo,NULL,jaco,(void *)vec1);
            rc = pthread_create(&tid, &attr, jaco, (void *)vec1);
            if (rc) {              
              printf("ERROR; return code from pthread_create() is %d\n", rc);
              exit(-1);
            }

              /* Wait for the thread */
            rc = pthread_join(tid, NULL);
            if (rc) {
              printf("ERROR; return code from pthread_join() is %d\n", rc);
              exit(-1);
            }
        
        /* Old data in utmp; new data in u */
        //for (i = 1; i < n; ++i)
        //    u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
      }
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
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
    //Defino variables  
    int i;
    int n, nsteps;  //cantidad n y n pasos
    double* u;      //defino un apuntador de doubles
    double* f;      //defino otro apuntador de doubles
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

    //LLeno todoas las n+1 posiciones de u con 0
    memset(u, 0, (n+1) * sizeof(double));
    //Lleno el segundo vector con h  (nunca supera 1) 
    for (i = 0; i <= n; ++i)
        f[i] = i * h;

    /*
    int k;
    for(k=0;k<n+1;k++)
        printf("aca%f\n",f[k] );
     */

    /* Run the solver */

    get_time(&tstart);
    jacobi(nsteps, n, u, f);
    get_time(&tend);

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
