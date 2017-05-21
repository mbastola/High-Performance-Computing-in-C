#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "circuitsat.h"

static int problem_size(int argc, char **argv)
{
    if (argc < 2)
        return 23;
    char *end = NULL;
    errno = 0;
    long n = strtol(argv[1], &end, 10);
    return (!errno && end != argv[1] && *end == '\0' && n >= 3 && n <= 62)
               ? (int)n : 23;
}

int main(int argc, char **argv)
{
    int rank, processes;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

    const int n = problem_size(argc, argv);
    const uint64_t combinations = UINT64_C(1) << n;
    uint64_t local = 0, total = 0;
    const double start = MPI_Wtime();

    for (uint64_t mask = (uint64_t)rank; mask < combinations;
         mask += (uint64_t)processes)
        local += (uint64_t)circuit_value(n, mask);

    MPI_Reduce(&local, &total, 1, MPI_UINT64_T, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("N=%d combinations=%" PRIu64 " solutions=%" PRIu64
               " processes=%d seconds=%.6f\n",
               n, combinations, total, processes, MPI_Wtime() - start);

    MPI_Finalize();
    return EXIT_SUCCESS;
}

