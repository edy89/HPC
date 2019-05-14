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
0 0
0.0001 5e-10
0.0002 1e-09
0.0003 1.5e-09
0.0004 2e-09
0.0005 2.5e-09
0.0006 3e-09
0.0007 3.5e-09
0.0008 4e-09
0.0009 4.5e-09
0.001 5e-09
0.0011 5.5e-09
0.0012 6e-09
0.0013 6.5e-09
0.0014 7e-09
0.0015 7.5e-09
0.0016 8e-09
0.0017 8.5e-09
0.0018 9e-09
0.0019 9.5e-09
0.002 1e-08
0.0021 1.05e-08
0.0022 1.1e-08
0.0023 1.15e-08



0.9974 3.88281e-06
0.9975 3.80813e-06
0.9976 3.72915e-06
0.9977 3.64569e-06
0.9978 3.55755e-06
0.9979 3.46455e-06
0.998 3.36649e-06
0.9981 3.26315e-06
0.9982 3.15433e-06
0.9983 3.03981e-06
0.9984 2.91939e-06
0.9985 2.79284e-06
0.9986 2.65993e-06
0.9987 2.52044e-06
0.9988 2.37414e-06
0.9989 2.2208e-06
0.999 2.06018e-06
0.9991 1.89203e-06
0.9992 1.71613e-06
0.9993 1.53223e-06
0.9994 1.34007e-06
0.9995 1.13942e-06
0.9996 9.30026e-07
0.9997 7.11637e-07
0.9998 4.84005e-07
0.9999 2.46876e-07
1 0



 */
void jacobi(int nsweeps, int n, double* u, double* f)
{
    int i, sweep,k;
    double h  = 1.0 / n;
    double h2 = h*h;
    double* utmp = (double*) malloc( (n+1) * sizeof(double) );

    /* Fill boundary conditions into utmp */
    /*
    utmp[0] = u[0];
    utmp[n] = u[n];


    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        
        for (i = 1; i < n; ++i)
            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
        
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
    }
    */
    //int mitad=nsweeps/2;

    utmp[0] = u[0];
    utmp[n] = u[n];


    for (sweep = 0; sweep < nsweeps; sweep += 2) {
        //printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeee%d\n",sweep );
        /* Old data in u; new data in utmp */
        for (i = 1; i < n; i++){

            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
            }
        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
        {
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
        }

    }

    /*for (k = mitad; k < nsweeps; k += 2) {
        
        for (i = 1; i < n; ++i)
            utmp[i] = (u[i-1] + u[i+1] + h2*f[i])/2;
        
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i-1] + utmp[i+1] + h2*f[i])/2;
    }*/


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

    /* Run the solver */   
     
    printf("n: %d\n"
           "nsteps: %d\n"
           "Elapsed time: %g s\n", 
           n, nsteps, timespec_diff(tstart, tend));

    if (fname)
        write_solution(n, u, fname);
    
    free(f);
    free(u);
    return 0;
}
