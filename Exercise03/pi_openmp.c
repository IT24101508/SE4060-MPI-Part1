#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 10000000LL

int main()
{
    long long inside = 0;
    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed =
            12345 + omp_get_thread_num();

        long long local_inside = 0;

        #pragma omp for
        for (long long i = 0; i < NUM_POINTS; i++)
        {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if ((x * x + y * y) <= 1.0)
            {
                local_inside++;
            }
        }

        #pragma omp atomic
        inside += local_inside;
    }

    end = omp_get_wtime();

    double pi =
        4.0 * (double)inside / (double)NUM_POINTS;

    printf("Number of threads: %d\n", omp_get_max_threads());
    printf("Total points = %lld\n", NUM_POINTS);
    printf("Points inside circle = %lld\n", inside);
    printf("Estimated Pi = %.10f\n", pi);
    printf("Execution time = %.6f seconds\n", end - start);

    return 0;
}
