/* ex8.c
OpenMP parallel for example
*/

#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel for
    for(int i = 1; i <= 10; i++)
    {
        printf("Iteration %d executed by thread %d\n", i, omp_get_thread_num());
    }

    return 0;
}
