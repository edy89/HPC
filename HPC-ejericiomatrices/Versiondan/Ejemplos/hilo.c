#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct thread_vars_t
{
  int number;
  pthread_mutex_t mutex;
};


struct invento
{
  int num;
  pthread_mutex_t mutex;
};

int numberExists(int arr[], int current)
{
  int i;

  for (i=0; i<current; ++i)
    {
      if (arr[current]==arr[i])
    return 1;
    }

  return 0;
}

void numberSearch()
{
  /* A time taking task */
  int numbers[100];
  int i;

  for (i=0; i<100; ++i)
    {
      numbers[i] = rand()%101;
      while (numberExists(numbers, i))
    numbers[i] = rand()%101;
    }
}


void *newtask(void *_number)
{
  struct thread_vars_t *vars = _number;

  /* BLOCK */
  pthread_mutex_lock(&vars->mutex);
  /* BLOCK */
  /*
  int number = vars->number;
  numberSearch();
  vars->number = number+1;
  */



  /* UNBLOCK */
  pthread_mutex_unlock(&vars->mutex);
  /* UNBLOCK */

  printf ("THREAD: number = %d\n", vars->number);

  pthread_exit(NULL);
}

void *newtask2(void *_number)
{
  struct invento *x = _number;

  /* BLOCK */
  //pthread_mutex_lock(&x->mutex);
  /* BLOCK */
  
  //int number = x->number;
  //numberSearch();
  int i;
  for(i=0;i<x->num;i++){
    numberSearch();
  }
  //x->number = number+1;
  x->num = x->num +1;
  printf("%d num\n", x->num);


  /* UNBLOCK */
  //pthread_mutex_unlock(&x->mutex);
  /* UNBLOCK */

  //printf ("THREAD: number = %d\n", vars->number);

  pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
   pthread_t thread;
   int rc;
   int i;
   struct thread_vars_t *vars = malloc (sizeof(struct thread_vars_t));
   struct invento *estructura = malloc (sizeof(struct invento));

   pthread_mutex_init(&vars->mutex, NULL);
   vars->number = 0;
   estructura->num=2;
   printf ("Main process just started.\n");
   /*
   for (i=0; i<10; ++i)
     {
       pthread_create(&thread, NULL, newtask, vars);
       //printf("%d\n", rc);
      
     }
  */
   for (i=0; i<5000; ++i)
     {
       pthread_create(&thread, NULL, newtask2, estructura);
       printf("%d invento \n", estructura->num);
      
     }

   printf ("Main process about to finish.\n");
   /* Last thing that main() should do */
   pthread_exit(NULL);
}