/* ex10.c
OpenMP synchronization example
*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int counter = 0;
    omp_lock_t lock;

    omp_init_lock(&lock);

    #pragma omp parallel num_threads(4)
    {
        #pragma omp atomic
        counter++;

        #pragma omp critical
        {
            printf("Thread %d entered critical section\n", omp_get_thread_num());
        }

        omp_set_lock(&lock);
        printf("Thread %d using lock\n", omp_get_thread_num());
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);

    printf("Final Counter = %d\n", counter);

    return 0;
}
