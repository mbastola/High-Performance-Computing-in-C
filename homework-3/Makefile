CC ?= gcc
MPICC ?= mpicc
CFLAGS ?= -O2 -std=c11 -Wall -Wextra -pedantic

.PHONY: all omp mpi clean

all: omp

omp: circuitsat_omp
mpi: circuitsat_mpi

circuitsat_omp: circuitsat_omp.c circuitsat.h
	$(CC) $(CFLAGS) -fopenmp -o $@ circuitsat_omp.c

circuitsat_mpi: circuitsat_mpi.c circuitsat.h
	$(MPICC) $(CFLAGS) -o $@ circuitsat_mpi.c

clean:
	rm -f circuitsat_omp circuitsat_mpi

