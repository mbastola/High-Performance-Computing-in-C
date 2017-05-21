MPICC ?= mpicc
CFLAGS ?= -O3 -std=c11 -Wall -Wextra -pedantic

.PHONY: all clean

all: nbody_mpi

nbody_mpi: nbody_mpi.c
	$(MPICC) $(CFLAGS) -o $@ $< -lm

clean:
	rm -f nbody_mpi

