#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "timing.h"


double jacobi_values(int n, double* u, double* f,int i)
{
    double h  = 1.0 / n;
    double h2 = h*h;
    double utmp;

    utmp = (u[i-1] + u[i+1] + h2*f[i])/2;
    
    return utmp;
}


void write_solution(int n, double* u, const char* fname)
{
    int i;
    double h = 1.0 / n;
    FILE* fp = fopen(fname, "w+");
    for (i = 0; i <= n; ++i)
        fprintf(fp, "[%g]  [%g] \n", i*h, u[i]);
    fclose(fp);
}


int main(int argc, char** argv)
{
    int i;
    int n, nsteps,sweep;
    double* u;
    double* f;
    double* aux;
    double h;
    timing_t tstart, tend;
    char* fname;
    pid_t pid;


    /* Process arguments */
    n      = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname  = (argc > 3) ? argv[3] : NULL;
    h      = 1.0/n;


    /* Allocate and initialize arrays */
    u   = (double*) calloc( (n+1), sizeof(double) );
    f   = (double*) malloc( (n+1) * sizeof(double) );
    aux = (double*) malloc( (n+1) * sizeof(double) );
    
    for (i = 0; i <= n; ++i)
        f[i] = i * h;

    aux[0] = u[0];
    aux[n] = u[n];

    /* Run the solver */
    get_time(&tstart);
         for(i = 1; i < n; ++i) 
            {
              pid= fork(); //Crea el proceso hijo
              for (sweep = 0; sweep < nsteps; sweep += 2)
              {
              	aux[i]  = jacobi_values(n, u, f,i);
              	u[i] = jacobi_values(n, aux, f,i);
              }
              
              if(pid != 0) //ve si el proceso hijo termino de ejecutarse
                break; 
            }
         if(pid!= 0)
          {
            wait(NULL);
            exit(0);
          }         
    get_time(&tend);
    

    /* Run the solver */    
    /*printf("n: %d\n"
           "nsteps: %d\n"
           "Elapsed time: %g s\n", 
            n, nsteps,timespec_diff(tend, tstart));*/

    printf("%g\n", timespec_diff(tend, tstart));

    if (fname)
       write_solution(n, u, fname);

    free(f);
    free(u);
    free(aux);

  return 0;
}