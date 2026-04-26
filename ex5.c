/* ex5.c
Pthreads Sum of Array using Multiple Threads
*/

#include <stdio.h>
#include <pthread.h>

int arr[10] = {1,2,3,4,5,6,7,8,9,10};
int sum1 = 0, sum2 = 0;

void *part1(void *arg)
{
    for(int i=0;i<5;i++)
        sum1 += arr[i];

    pthread_exit(NULL);
}

void *part2(void *arg)
{
    for(int i=5;i<10;i++)
        sum2 += arr[i];

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, part1, NULL);
    pthread_create(&t2, NULL, part2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum = %d\n", sum1 + sum2);

    return 0;
}
