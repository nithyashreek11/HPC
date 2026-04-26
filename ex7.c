/* ex7.c
Pthreads synchronization using semaphore
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0;
sem_t s;

void *increment(void *arg)
{
    for(int i = 0; i < 10000; i++)
    {
        sem_wait(&s);
        counter++;
        sem_post(&s);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;

    sem_init(&s, 0, 1);

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final Counter = %d\n", counter);

    sem_destroy(&s);
    return 0;
}
