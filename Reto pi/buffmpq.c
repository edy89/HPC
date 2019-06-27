# include <math.h>
# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main ( int argc, char *argv[] );
int buffon ( double a, double b, double l, int trial_num );
double huge ( );
void timers ( );

int main ( int argc, char *argv[] )
{
  double a = 1.0;
  double b = 1.0;
  int hit_num;
  int hit_total;
  int ierr;
  double l = 1.0;
  int master = 0;
  double pdf_estimate;
  double pi = 3.141592653589793238462643;
  double pi_error;
  double pi_estimate;
  int process_num;
  int process_rank;
  double random_value;
  int seed;
  int trial_num = 25;
  int trial_total;
  ierr = MPI_Init ( &argc, &argv );
  ierr = MPI_Comm_size ( MPI_COMM_WORLD, &process_num );
  ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &process_rank );
  if ( process_rank == master ) 
  {
    timers ( );
    t1=MPI_Wtime();
    printf ( "  The number of processes is %d\n", process_num );
  }
  seed = 123456789 + process_rank * 100;
  srand ( seed );
  random_value  = ( double ) rand ( ) / ( double ) RAND_MAX;
  printf ( "  %8d  %12d  %14f\n", process_rank, seed, random_value );
  hit_num = buffon ( a, b, l, trial_num );
  ierr = MPI_Reduce ( &hit_num, &hit_total, 1, MPI_INT, MPI_SUM, master, 
    MPI_COMM_WORLD );
  if ( process_rank == master )
  {
    trial_total = trial_num * process_num;
    pdf_estimate = ( double ) ( hit_total ) / ( double ) ( trial_total );
    if ( hit_total == 0 )
    {
      pi_estimate = huge ( );
    }
    else
    {
      pi_estimate = l * ( 2.0 * ( a + b ) - l ) / ( a * b * pdf_estimate );
    }
    pi_error = fabs ( pi - pi_estimate );
    printf ( "\n" );
    printf ( 
      "    Trials      Hits    Estimated PDF       Estimated Pi        Error\n" );
    printf ( "\n" );
    printf ( "  %8d  %8d  %16.12f  %16.12f  %16.12f\n",
      trial_total, hit_total, pdf_estimate, pi_estimate, pi_error );
  }
  t2=MPI_Wtime();
  ierr = MPI_Finalize ( );
  if ( process_rank == master )
  {
    printf ( "\n" );
    printf ( "BUFFON \n" );
    printf ( "  Exit with no errors\n" );
    printf ( "  Estimated time %f\n",t2-t1 );
    printf ( "\n" );
    timers ( );
  }
  return 0;
}

int buffon ( double a, double b, double l, int trial_num )
{
  double angle;
  int hits;
  double pi = 3.141592653589793238462643;
  int trial;
  double x1;
  double x2;
  double y1;
  double y2;
  hits = 0;
  for ( trial = 1; trial <= trial_num; trial++ )
  {
/*
  Randomly choose the location of the eye of the needle in [0,0]x[A,B],
  and the angle the needle makes.
*/
    x1 = a * ( double ) rand ( ) / ( double ) RAND_MAX;
    y1 = b * ( double ) rand ( ) / ( double ) RAND_MAX;
    angle = 2.0 * pi * ( double ) rand ( ) / ( double ) RAND_MAX;
/*
  Compute the location of the point of the needle.
*/
    x2 = x1 + l * cos ( angle );
    y2 = y1 + l * sin ( angle );
/*
  Count the end locations that lie outside the cell.
*/
    if ( x2 <= 0.0 || a <= x2 || y2 <= 0.0 || b <= y2 )
    {
      hits = hits + 1;
    }
  }
  return hits;
}

double huge ( )
{
  double value;
  value = 1.0E+30;
  return value;
}

void timers ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;
  now = time ( NULL );
  tm = localtime ( &now );
  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );
  printf ( "%s\n", time_buffer );
  return;
# undef TIME_SIZE
}

/*
Thanks to John Burkardt for helps with the code
*/