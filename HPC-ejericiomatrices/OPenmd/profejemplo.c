#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int p, th_id;
	//p=omp_get_num_procs();
	//p=5;
	//printf("%d\n",p );
	//omp_set_num_threads(p);
	#pragma omp parallel private(th_id)
	{
		th_id=omp_get_thread_num();
		printf(" Привет, мирthread  %d\n",th_id );
	}
	return 0;
}