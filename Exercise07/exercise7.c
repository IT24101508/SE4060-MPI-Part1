#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int x;
    int y;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 1 || rank == 2)
    {
        if (rank == 1)
            x = 30;
        else
            x = 50;

        int buffer_size;

        MPI_Pack_size(
            1,
            MPI_INT,
            MPI_COMM_WORLD,
            &buffer_size
        );

        buffer_size += MPI_BSEND_OVERHEAD;

        void *buffer = malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        printf(
            "Rank %d: Sending %d using MPI_Bsend\n",
            rank,
            x
        );

        MPI_Bsend(
            &x,
            1,
            MPI_INT,
            3,
            0,
            MPI_COMM_WORLD
        );

        MPI_Buffer_detach(&buffer, &buffer_size);

        free(buffer);
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
