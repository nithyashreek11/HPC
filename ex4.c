/* ex4.c
MPI Structure Communication
*/

#include <stdio.h>
#include <mpi.h>

struct Student
{
    int roll;
    float mark;
};

int main(int argc, char *argv[])
{
    int rank;
    struct Student s;

    MPI_Datatype newtype;
    int blocklengths[2] = {1,1};
    MPI_Aint offsets[2];
    MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};

    offsets[0] = offsetof(struct Student, roll);
    offsets[1] = offsetof(struct Student, mark);

    MPI_Type_create_struct(2, blocklengths, offsets, types, &newtype);
    MPI_Type_commit(&newtype);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        s.roll = 101;
        s.mark = 95.5;
        MPI_Send(&s, 1, newtype, 1, 0, MPI_COMM_WORLD);
    }

    if(rank == 1)
    {
        MPI_Recv(&s, 1, newtype, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Roll = %d\n", s.roll);
        printf("Mark = %.2f\n", s.mark);
    }

    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}
