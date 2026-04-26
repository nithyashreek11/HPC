/* 
EXERCISE 1
Data Parallelism and Task Parallelism using Fork and
Inter Process Communication (Pipe)

Aim:
To demonstrate process creation using fork(),
task parallelism, data parallelism, and IPC using pipe.

Description:
1. Parent creates two child processes.
2. Child 1 calculates sum of first half of array.
3. Child 2 calculates sum of second half of array.
4. Both send result to parent using pipe.
5. Parent prints total sum.

Compile:
gcc ex1.c -o ex1

Run:
./ex1
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2;

    int sum1 = 0, sum2 = 0, total = 0;

    pipe(pipe1);
    pipe(pipe2);

    /* First Child Process */
    pid1 = fork();

    if(pid1 == 0)
    {
        for(int i = 0; i < 5; i++)
        {
            sum1 += arr[i];
        }

        write(pipe1[1], &sum1, sizeof(sum1));
        exit(0);
    }

    /* Second Child Process */
    pid2 = fork();

    if(pid2 == 0)
    {
        for(int i = 5; i < 10; i++)
        {
            sum2 += arr[i];
        }

        write(pipe2[1], &sum2, sizeof(sum2));
        exit(0);
    }

    /* Parent Process */
    wait(NULL);
    wait(NULL);

    read(pipe1[0], &sum1, sizeof(sum1));
    read(pipe2[0], &sum2, sizeof(sum2));

    total = sum1 + sum2;

    printf("Sum from Child 1 = %d\n", sum1);
    printf("Sum from Child 2 = %d\n", sum2);
    printf("Total Sum = %d\n", total);

    return 0;
}
