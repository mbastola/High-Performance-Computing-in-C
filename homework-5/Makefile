CC ?= gcc
NVCC ?= nvcc
CFLAGS ?= -O2 -std=c99 -Wall -Wextra -fopenmp -D_DEFAULT_SOURCE
NVCCFLAGS ?= -O2

.PHONY: all cpu cuda clean

all: cpu
cpu: nbody_cpu
cuda: nbody_cuda

nbody_cpu: nbody.c timer.h
	$(CC) $(CFLAGS) -o $@ nbody.c -lm

nbody_cuda: nbody.cu timer.h
	$(NVCC) $(NVCCFLAGS) -o $@ nbody.cu

clean:
	rm -f nbody_cpu nbody_cuda

