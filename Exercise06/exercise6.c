#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int x;
    int y;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 1)
    {
        x = 30;

        printf("Rank 1: Sending value %d to rank 3\n", x);

        MPI_Ssend(
            &x,
            1,
            MPI_INT,
            3,
            0,
            MPI_COMM_WORLD
        );
    }
    else if (rank == 2)
    {
        x = 50;

        printf("Rank 2: Sending value %d to rank 3\n", x);

        MPI_Ssend(
            &x,
            1,
            MPI_INT,
            3,
            0,
            MPI_COMM_WORLD
        );
    }
    else if (rank == 3)
    {
        MPI_Recv(
            &y,
            1,
            MPI_INT,
            MPI_ANY_SOURCE,
            0,
            MPI_COMM_WORLD,
            &status
        );

        printf(
            "Rank 3: Received %d from rank %d\n",
            y,
            status.MPI_SOURCE
        );
    }
    else
    {
        printf("Rank %d: Normal process\n", rank);
    }

    MPI_Finalize();

    return 0;
}
