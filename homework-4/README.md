## Homework 4 — MPI galaxy/N-body simulation

The report analyzes an MPI galaxy simulation and varies:

- number of stars `N` (observed quadratic work);
- integration time step `dt` (runtime roughly proportional to `1/dt`);
- stellar mass (no meaningful runtime dependence);
- MPI process count, including communication across machine boundaries; and
- compiler/OpenMP/random-number optimizations.

Its final model is of the form `a N²/(p dt) + b N p`: computation decreases
with `p`, while communication eventually dominates. The project is missing 
original program included `modeldata.cpp` and `diffeq.cpp`, Euler/Runge–Kutta
integration, and MPI.

## Artifacts and fidelity

- [Submitted report](HPCHw4.pdf)
- [`nbody_mpi.c`](nbody_mpi.c) implements the report's essential experiment: an
  all-pairs O(N²) force calculation distributed across MPI ranks, followed by
  `MPI_Allgatherv` communication and Euler integration.


## Build and run

```sh
make
mpirun -np 4 ./nbody_mpi 1024 200 8 1000
```

Arguments are `N`, mass, `dt`, and final time. For practical checks, use a small
final time; the historically reported `dt=8, final_time=1000` performs 125
steps.

