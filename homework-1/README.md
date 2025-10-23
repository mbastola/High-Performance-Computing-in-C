# Homework 1 — profiling and memory locality

The report establishes these topics (its printed question numbering skips from
2 to 4):

1. Compare `gprof`, `oprofile`/`operf`, and `perf`.
2. Compare profiler results with manual timing hooks.
3. Investigate compiler optimization levels (`-O0` through `-O3`).
4. Compare pre-multiplication (`vM`) with post-multiplication (`Mv`).
5. Measure how execution time scales with matrix/vector size.

The experiments used repeated dense vector–matrix multiplication and discussed
the effect of row-major spatial locality.

## Artifacts

- [Submitted report](hw1.pdf)
- [`hw1.c`](hw1.c): Function signatures
  were repaired and the fixed-size arrays were made dynamic so the historical
  `N=1024`, `REPS=1000` defaults can be overridden for quick checks.
- [`make.sh`](make.sh): shell script for make
- [`Makefile`](Makefile): includes optimization experiments named
  in the report.

## Build and run

```sh
make            # builds the -O2 version
./hw1 256 10    # size 256, ten repetitions
make profiles   # profiling-friendly binaries
bash make.sh     # measure a normal build in milliseconds
```

The appendix hard-coded `N=1024` and `REPS=1000`. The
program accepts smaller command-line values so it can be checked quickly while
retaining those defaults.

