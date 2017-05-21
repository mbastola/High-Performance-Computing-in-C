#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DEFAULT_N 1024
#define DEFAULT_REPS 1000
#define SEED 1

static double *vector_data;
static double *matrix_data;
static double *result;

static double elapsed_ms(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0 +
           (end.tv_usec - start.tv_usec) / 1000.0;
}

static int positive_int(const char *text, int fallback)
{
    char *end = NULL;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (errno || end == text || *end != '\0' || value <= 0 || value > 100000)
        return fallback;
    return (int)value;
}

static void initialize(int n)
{
    srand(SEED);
    for (int i = 0; i < n; ++i) {
        vector_data[i] = (double)rand() / RAND_MAX;
        result[i] = 0.0;
        for (int j = 0; j < n; ++j)
            matrix_data[(size_t)i * n + j] = (double)rand() / RAND_MAX;
    }
}

/* vM: walks down columns of a row-major matrix. */
static void vm_multiply(int n)
{
    for (int j = 0; j < n; ++j) {
        result[j] = 0.0;
        for (int i = 0; i < n; ++i)
            result[j] += vector_data[i] * matrix_data[(size_t)i * n + j];
    }
}

/* Mv: walks across rows of a row-major matrix. */
static void mv_multiply(int n)
{
    for (int j = 0; j < n; ++j) {
        result[j] = 0.0;
        for (int i = 0; i < n; ++i)
            result[j] += matrix_data[(size_t)j * n + i] * vector_data[i];
    }
}

int main(int argc, char **argv)
{
    const int n = argc > 1 ? positive_int(argv[1], DEFAULT_N) : DEFAULT_N;
    const int reps = argc > 2 ? positive_int(argv[2], DEFAULT_REPS) : DEFAULT_REPS;
    const size_t matrix_elements = (size_t)n * n;
    struct timeval start, end;

    vector_data = malloc((size_t)n * sizeof(*vector_data));
    matrix_data = malloc(matrix_elements * sizeof(*matrix_data));
    result = malloc((size_t)n * sizeof(*result));
    if (!vector_data || !matrix_data || !result) {
        fprintf(stderr, "allocation failed for N=%d\n", n);
        free(vector_data);
        free(matrix_data);
        free(result);
        return EXIT_FAILURE;
    }

    initialize(n);

    gettimeofday(&start, NULL);
    for (int i = 0; i < reps; ++i)
        vm_multiply(n);
    gettimeofday(&end, NULL);
    printf("vM: N=%d reps=%d %.3f ms checksum=%.9f\n",
           n, reps, elapsed_ms(start, end), result[n - 1]);

    gettimeofday(&start, NULL);
    for (int i = 0; i < reps; ++i)
        mv_multiply(n);
    gettimeofday(&end, NULL);
    printf("Mv: N=%d reps=%d %.3f ms checksum=%.9f\n",
           n, reps, elapsed_ms(start, end), result[n - 1]);

    free(vector_data);
    free(matrix_data);
    free(result);
    return EXIT_SUCCESS;
}

