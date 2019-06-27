#include <mpi.h>  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void userkey(int argc, char* argv[], int myRank, long* totalNumthrowes_p);
long throw (long Process, int myRank);
int main(int argc, char** argv) {
   //Definition unpits
   int myRank, numProcs;
   long totalNumthrowes, Process, processNumberInCircle, totalNumberInCircle;
   double start, finish, loc_elapsed, elapsed, piEstimate;
   double PI25DT = 3.141592653589793238462643;         /* 25-digit-PI*/
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
   MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
   userkey(argc, argv, myRank, &totalNumthrowes);  // Read total number of throwes from command line
   Process = totalNumthrowes/numProcs; 
   MPI_Barrier(MPI_COMM_WORLD);
   start = MPI_Wtime();
   processNumberInCircle = throw(Process, myRank);
   finish = MPI_Wtime();
   loc_elapsed = finish-start;
   MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); 
 
   MPI_Reduce(&processNumberInCircle, &totalNumberInCircle, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
   
   if (myRank == 0) {
	   piEstimate = (4*totalNumberInCircle)/((double) totalNumthrowes);
	   printf("Elapsed time = %f seconds \n", elapsed);
	   printf("Pi is approximately %.16f, Error is %.16f\n", piEstimate, fabs(piEstimate - PI25DT));
   }
   MPI_Finalize(); 
   return 0;
}  

/* Function gets input from command line for totalNumthrowes */
void userkey(int argc, char* argv[], int myRank, long* totalNumthrowes_p){
	if (myRank == 0) {
		if (argc!= 2){
		    fprintf(stderr, "usage: mpirun -np <N> %s <number of throwes> \n", argv[0]);
            fflush(stderr);
            *totalNumthrowes_p = 0;
		} else {
			*totalNumthrowes_p = atoi(argv[1]);
		}
	}
	// Broadcasts value of totalNumthrowes to each process
	MPI_Bcast(totalNumthrowes_p, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	
	// 0 totalNumthrowes ends the program
    if (*totalNumthrowes_p == 0) {
        MPI_Finalize();
        exit(-1);
    }
}
/* Function implements Monte Carlo version of throwing darts at a board */
long throw (long processthrowes, int myRank){
	long throw, numberInCircle = 0;        
	double x,y;
	unsigned int seed = (unsigned) time(NULL);
	srand(seed + myRank);
	for (throw = 0; throw < processthrowes; throw++) {
	   x = rand_r(&seed)/(double)RAND_MAX;
	   y = rand_r(&seed)/(double)RAND_MAX;
	   if((x*x+y*y) <= 1.0 ) numberInCircle++;
    }
    return numberInCircle;
}

/*   
 Thanks to Hannah Sonsalla to help us with the code
 */