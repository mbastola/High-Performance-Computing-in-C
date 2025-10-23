# Homework 5 — CUDA N-body simulation

The report compares a 16-thread OpenMP CPU implementation with CUDA, explores
block/thread geometry and problem-size scaling, and attempts optimizations to
the force kernel and host/device memory transfers.

## Authoritative artifacts

- [Submitted report](HPCHW5.pdf)
- [`nbody.c`](nbody.c): surviving OpenMP CPU baseline, copied locally.
- [`nbody.cu`](nbody.cu): surviving CUDA baseline, copied locally.
- [`timer.h`](timer.h): shared historical timer implementation.
- [Final/experimental CUDA variant](historical-artifacts/knbody.cu)
- [CUDA learning exercises](cuda-exercises/)


## Notes

Several CUDA variants are experiments the report explicitly calls unsuccessful.
Some contain indexing or timing errors and should not be treated as polished
solutions. `nbody.cu` is the clearest baseline; `knbody.cu`, `knbody2.cu`,
`knbody3.cu`, `knbody4.cu`, `new.cu`, and `prob4.cu` preserve optimization work.

The local Makefile builds the copied CPU or CUDA baseline:

```sh
make cpu
OMP_NUM_THREADS=16 ./nbody_cpu 30000

make cuda
./nbody_cuda 30000
```

The CPU target defines `_DEFAULT_SOURCE` because `timer.h` uses the BSD/GNU
`timersub` macro, which is hidden by modern compilers in strict C mode.

