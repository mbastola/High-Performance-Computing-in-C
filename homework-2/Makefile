CC ?= gcc
CFLAGS ?= -O2 -std=c11 -Wall -Wextra -fopenmp

.PHONY: all gprof operf perf scalasca clean

all: heated_plate monte_carlo

heated_plate: heated_plate_open_mp.c
	$(CC) $(CFLAGS) -o $@ heated_plate_open_mp.c -lm

monte_carlo: monte_carlo.c
	$(CC) $(CFLAGS) -o $@ monte_carlo.c -lm

gprof: heated_plate_open_mp.c
	$(CC) $(CFLAGS) -pg -o heated_plate heated_plate_open_mp.c -lm

operf: heated_plate_open_mp.c
	$(CC) $(CFLAGS) -g -o heated_plate heated_plate_open_mp.c -lm

perf: heated_plate_open_mp.c
	$(CC) $(CFLAGS) -ggdb -o heated_plate heated_plate_open_mp.c -lm

scalasca: heated_plate_open_mp.c
	scalasca -instrument $(CC) $(CFLAGS) -o heated_plate heated_plate_open_mp.c -lm

clean:
	rm -f heated_plate monte_carlo gmon.out

