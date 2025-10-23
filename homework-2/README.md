# Homework 2 — OpenMP heated plate and Monte Carlo solver

This compares the iterative
finite-difference heated-plate solver with an OpenMP Monte Carlo random-walk
solution, profiles the code with Scalasca, and studies tolerance, plate size,
and thread count.

## Authoritative artifacts

- [Report](HPCHW2.pdf)
- [Heated-plate source](heated_plate_open_mp.c)
- [Monte Carlo source](monte_carlo.c)
- [Build file](Makefile)
- [Heated-plate run script](heated_plate_run.sh)
- [Scalasca run script](heated_plate_run_scalasca.sh)
- [Monte Carlo run script](monte_carlo_run.sh)

The local Makefile builds both programs:

```sh
make
OMP_NUM_THREADS=4 ./heated_plate
OMP_NUM_THREADS=4 ./monte_carlo
```

## Notes

Its `rand_r` seed is based on
`time(NULL)` inside each walk, so simultaneous walks can reuse seeds; the report
itself discusses random-number accuracy concerns. Its boundary check also uses
`M` for both dimensions, harmless for the submitted square 500×500 plate but not
for a rectangular grid.

