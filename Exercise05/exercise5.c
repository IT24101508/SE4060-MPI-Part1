#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int x = 30;
    int y;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 1)
    {
        printf("Rank 1: Sending message to rank 2\n");

        MPI_Ssend(
            &x,
            1,
            MPI_INT,
            2,
            0,
            MPI_COMM_WORLD
        );

        printf("Rank 1: Message sent\n");
    }
    else if (rank == 3)
    {
        printf("Rank 3: Waiting for message from rank 1\n");

        MPI_Recv(
            &y,
            1,
            MPI_INT,
            1,
            0,
            MPI_COMM_WORLD,
            &status
        );

        printf("Rank 3: Received value = %d\n", y);
    }
    else
    {
        printf("Rank %d: Normal process\n", rank);
    }

    MPI_Finalize();

    return 0;
}
