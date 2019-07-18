#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//#pragma omp parallel for

#include <stdio.h>
#include <omp.h>
int main(){
 int x;

 x = 2;
 printf("%d\n", x);
 #pragma omp parallel num_threads(14) shared(x)
 {
 if (omp_get_thread_num() == 0) {
 x = 5; 
 printf("0: true Thread# %d: x = %d\n", omp_get_thread_num(),x );
 } else {
 /* Print 1: the following read of x has a race */
 printf("1: falseThread# %d: x = %d\n", omp_get_thread_num(),x );
 }
 printf("wait\n");
 #pragma omp barrier
 if (omp_get_thread_num() == 0) {
 /* Print 2 */
 printf("2: Thread# %d: x = %d\n", omp_get_thread_num(),x );
 } else {
 /* Print 3 */
 printf("3: Thread# %d: x = %d\n", omp_get_thread_num(),x );
 }
 }
 return 0;

}