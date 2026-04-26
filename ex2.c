/* ex2.c
MPI program using Send and Receive
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, num = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent %d to Process 1\n", num);
    }
    else if(rank == 1)
    {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received %d from Process 0\n", num);
    }

    MPI_Finalize();
    return 0;
}
