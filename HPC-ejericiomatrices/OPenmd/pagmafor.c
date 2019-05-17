#include <stdio.h>
#include <omp.h>

#define LARGO 1000

int main(int argc, char const *argv[])
{
    int valores[LARGO];

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < LARGO; ++i)
        {
            valores[i] = i;
            printf("a\n");
        }
    }
    return 0;
}