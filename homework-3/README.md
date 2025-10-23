# Homework 3 — OpenMP versus MPI CircuitSAT

## Reconstructed assignment

The report compares OpenMP and MPI implementations of brute-force Boolean
circuit satisfiability using Scalasca. It investigates:

1. runtime-management and synchronization overhead;
2. exponential scaling with Boolean-vector size `N`;
3. MPI process-count scaling;
4. OpenMP thread-count scaling; and
5. a performance model approximately proportional to `2^N / p` in the measured
   range.

## Artifacts and fidelity

- [Submitted report](HPCHw3.pdf)
- [`circuitsat_omp.c`](circuitsat_omp.c) and
  [`circuitsat_mpi.c`](circuitsat_mpi.c) are **behavioral reconstructions**.

The original sources are absent. The report provides the generalized circuit
expression `(b[i] || b[i+1]) && (!b[i+1] || !b[i+2])`; the reconstructions use
that expression and exhaustive bit-vector enumeration. They reproduce the work
partitioning needed for the reported experiments but are not claimed to be the
submitted files.

## Build and examples

```sh
make omp
OMP_NUM_THREADS=16 ./circuitsat_omp 23

make mpi
mpirun -np 16 ./circuitsat_mpi 23
```

The MPI target requires an MPI development environment (`mpicc` and `mpirun`).

