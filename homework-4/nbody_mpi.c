/* Behavioral reconstruction from HPCHw4.pdf; not the original submission. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

typedef struct {
    double x, y, z;
    double vx, vy, vz;
} Body;

static int parse_int(const char *s, int fallback)
{
    char *end = NULL;
    long value = strtol(s, &end, 10);
    return end != s && *end == '\0' && value > 0 ? (int)value : fallback;
}

static double parse_double(const char *s, double fallback)
{
    char *end = NULL;
    double value = strtod(s, &end);
    return end != s && *end == '\0' && value > 0.0 ? value : fallback;
}

static void initialize(Body *bodies, int n)
{
    srand(1);
    for (int i = 0; i < n; ++i) {
        bodies[i].x = 2.0 * rand() / RAND_MAX - 1.0;
        bodies[i].y = 2.0 * rand() / RAND_MAX - 1.0;
        bodies[i].z = 2.0 * rand() / RAND_MAX - 1.0;
        bodies[i].vx = bodies[i].vy = bodies[i].vz = 0.0;
    }
}

int main(int argc, char **argv)
{
    int rank, processes;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

    const int n = argc > 1 ? parse_int(argv[1], 1024) : 1024;
    const double mass = argc > 2 ? parse_double(argv[2], 200.0) : 200.0;
    const double dt = argc > 3 ? parse_double(argv[3], 8.0) : 8.0;
    const double final_time = argc > 4 ? parse_double(argv[4], 1000.0) : 1000.0;
    const int steps = (int)ceil(final_time / dt);
    const double softening = 1e-9;

    int *counts = malloc((size_t)processes * sizeof(*counts));
    int *offsets = malloc((size_t)processes * sizeof(*offsets));
    int *byte_counts = malloc((size_t)processes * sizeof(*byte_counts));
    int *byte_offsets = malloc((size_t)processes * sizeof(*byte_offsets));
    Body *bodies = malloc((size_t)n * sizeof(*bodies));
    if (!counts || !offsets || !byte_counts || !byte_offsets || !bodies) {
        fprintf(stderr, "rank %d: allocation failure\n", rank);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int cursor = 0;
    for (int p = 0; p < processes; ++p) {
        counts[p] = n / processes + (p < n % processes);
        offsets[p] = cursor;
        byte_counts[p] = counts[p] * (int)sizeof(Body);
        byte_offsets[p] = cursor * (int)sizeof(Body);
        cursor += counts[p];
    }
    const int begin = offsets[rank];
    const int local_n = counts[rank];
    Body *updated = malloc((size_t)local_n * sizeof(*updated));
    if (!updated) {
        fprintf(stderr, "rank %d: allocation failure\n", rank);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (rank == 0)
        initialize(bodies, n);
    MPI_Bcast(bodies, n * (int)sizeof(Body), MPI_BYTE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    const double start = MPI_Wtime();

    for (int step = 0; step < steps; ++step) {
        for (int local = 0; local < local_n; ++local) {
            const int i = begin + local;
            Body next = bodies[i];
            double ax = 0.0, ay = 0.0, az = 0.0;
            for (int j = 0; j < n; ++j) {
                const double dx = bodies[j].x - bodies[i].x;
                const double dy = bodies[j].y - bodies[i].y;
                const double dz = bodies[j].z - bodies[i].z;
                const double r2 = dx * dx + dy * dy + dz * dz + softening;
                const double inv_r3 = 1.0 / (sqrt(r2) * r2);
                ax += mass * dx * inv_r3;
                ay += mass * dy * inv_r3;
                az += mass * dz * inv_r3;
            }
            next.vx += dt * ax;
            next.vy += dt * ay;
            next.vz += dt * az;
            next.x += dt * next.vx;
            next.y += dt * next.vy;
            next.z += dt * next.vz;
            updated[local] = next;
        }
        MPI_Allgatherv(updated, local_n * (int)sizeof(Body), MPI_BYTE,
                       bodies, byte_counts, byte_offsets, MPI_BYTE,
                       MPI_COMM_WORLD);
    }

    const double elapsed = MPI_Wtime() - start;
    if (rank == 0)
        printf("N=%d mass=%g dt=%g final=%g steps=%d processes=%d seconds=%.6f checksum=%.9g\n",
               n, mass, dt, final_time, steps, processes, elapsed,
               bodies[n - 1].x + bodies[n - 1].y + bodies[n - 1].z);

    free(updated);
    free(bodies);
    free(byte_offsets);
    free(byte_counts);
    free(offsets);
    free(counts);
    MPI_Finalize();
    return EXIT_SUCCESS;
}

