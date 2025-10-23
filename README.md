# CSE 566: High Performance Computing

**Washington University in St. Louis · 2017 · Graduate coursework**

This portfolio presents my work in CSE 566, a graduate course focused on the
analysis, implementation, and empirical evaluation of high-performance
computing systems. Across five programming assignments and a final research
project, I progressed from single-node performance analysis to shared-memory,
distributed-memory, and GPU computing.

My emphasis throughout the course was not simply to parallelize code, but to
measure where performance came from: cache locality, compiler optimization,
synchronization, communication, workload size, processor count, and accelerator
execution geometry. The submitted reports combine experimental data with
performance models and discussions of the limits of each approach.

## Project portfolio

| Project | Technical focus | Work and results |
| --- | --- | --- |
| [Homework 1](homework-1/README.md) | Profiling, optimization, and memory locality | Compared `gprof`, `oprofile`/`operf`, `perf`, and manual timing on dense vector–matrix multiplication. Evaluated GCC optimization levels and demonstrated the performance effect of row-major access patterns. |
| [Homework 2](homework-2/README.md) | OpenMP and numerical methods | Parallelized an iterative heated-plate solver and implemented a Monte Carlo random-walk solution to the Laplace equation. Used Scalasca to study management and synchronization overhead while varying tolerance, problem size, and thread count. |
| [Homework 3](homework-3/README.md) | OpenMP versus MPI | Analyzed brute-force Boolean circuit satisfiability under shared- and distributed-memory execution. Measured exponential problem scaling, process/thread scaling, and communication overhead, then developed a performance model proportional to `2^N / p` over the measured range. |
| [Homework 4](homework-4/README.md) | Distributed N-body simulation | Studied an MPI galaxy simulation as a function of particle count, integration step, mass, and process count. Modeled the tradeoff between O(N²) force computation and inter-process communication, and measured an approximately 4× improvement from compiler optimization in the reported configuration. |
| [Homework 5](homework-5/README.md) | CUDA acceleration | Ported the N-body workload to CUDA and investigated block size, grid size, problem scaling, memory transfers, and kernel design. The submitted experiments measured approximately 42× GPU speedup over the 16-thread CPU baseline for 30,000 bodies. |
| [Final project](final-project/README.md) | Quantum computing and HPC architecture | Wrote a literature critique of quantum processing units as HPC accelerators, focusing on QRAM, quantum interconnects, loose versus tight integration, scalability, fault tolerance, and the limitations of FLOPS-based metrics. |

## Technical scope

- Languages and models: C, C++, OpenMP, MPI, and CUDA
- Performance tools: Scalasca, `gprof`, `perf`, `operf`, and `nvprof`
- Workloads: dense linear algebra, steady-state heat diffusion, Monte Carlo
  methods, CircuitSAT, and direct N-body simulation
- Analysis: strong-scaling behavior, asymptotic complexity, cache locality,
  compiler optimization, thread/process overhead, GPU execution geometry, and
  compute-to-communication tradeoffs
- Platforms: Linux workstations, the Washington University computing cluster,
  and NVIDIA GPU hardware

## Repository layout

Each project directory contains its report, source code, build instructions,
and the available experimental material. Start with the project README, then
consult the submitted PDF for the complete methodology, plots, and analysis.

```text
homework-1/     Profiling and vector–matrix multiplication
homework-2/     OpenMP heated plate and Monte Carlo solver
homework-3/     OpenMP/MPI CircuitSAT
homework-4/     MPI galaxy and N-body simulation
homework-5/     CUDA N-body acceleration
final-project/  Quantum processing units in HPC
```

The five projects were completed with a collaborator, as credited in
the submissions. The final research project was completed individually.

