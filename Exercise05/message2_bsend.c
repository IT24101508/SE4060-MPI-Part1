#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    int x[10];
    int y[10];
    int buffer_size;
    void *buffer;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 1)
    {
        for (int r = 0; r < 10; r++)
        {
            x[r] = 10 * r;
        }

        MPI_Pack_size(
            10,
            MPI_INT,
            MPI_COMM_WORLD,
            &buffer_size
        );

        buffer_size += MPI_BSEND_OVERHEAD;

        buffer = malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        printf("Rank 1: Sending array to rank 3 using MPI_Bsend\n");

        MPI_Bsend(
            x,
            10,
            MPI_INT,
            3,
            0,
            MPI_COMM_WORLD
        );

        printf("Rank 1: Buffered send completed\n");

        MPI_Buffer_detach(&buffer, &buffer_size);

        free(buffer);
    }
    else if (rank == 3)
    {
        MPI_Recv(
            y,
            10,
            MPI_INT,
            1,
            0,
            MPI_COMM_WORLD,
            &status
        );

        printf("Rank 3: Received values:\n");

        for (int r = 0; r < 10; r++)
        {
            printf("%d ", y[r]);
        }

        printf("\n");
    }
    else
    {
        printf("Rank %d: Normal process\n", rank);
    }

    MPI_Finalize();

    return 0;
}
