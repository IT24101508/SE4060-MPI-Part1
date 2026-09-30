#include <stdio.h>
#include <omp.h>

#define N 10000000LL

int main()
{
    long long total = 0;
    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:total)
    for (long long i = 1; i <= N; i++)
    {
        total += i;
    }

    end = omp_get_wtime();

    printf("Number of threads: %d\n", omp_get_max_threads());
    printf("Total sum = %lld\n", total);
    printf("Expected sum = 50000005000000\n");
    printf("Execution time = %.6f seconds\n", end - start);

    return 0;
}
