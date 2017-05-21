#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
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
    const int n = problem_size(argc, argv);
    const uint64_t combinations = UINT64_C(1) << n;
    uint64_t solutions = 0;
    const double start = omp_get_wtime();

#pragma omp parallel for reduction(+ : solutions) schedule(static)
    for (uint64_t mask = 0; mask < combinations; ++mask)
        solutions += (uint64_t)circuit_value(n, mask);

    printf("N=%d combinations=%" PRIu64 " solutions=%" PRIu64
           " threads=%d seconds=%.6f\n",
           n, combinations, solutions, omp_get_max_threads(),
           omp_get_wtime() - start);
    return EXIT_SUCCESS;
}

