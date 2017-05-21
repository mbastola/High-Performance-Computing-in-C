CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -pedantic

.PHONY: all norm o0 o1 o2 o3 profiles clean

all: norm

norm: hw1.c
	$(CC) $(CFLAGS) -O2 -o hw1 hw1.c

o0 o1 o2 o3: hw1.c
	$(CC) $(CFLAGS) -O$(@:o%=%) -o hw1-$@ hw1.c

profiles: hw1-gprof hw1-debug

hw1-gprof: hw1.c
	$(CC) $(CFLAGS) -O0 -pg -o $@ $<

hw1-debug: hw1.c
	$(CC) $(CFLAGS) -O0 -g -o $@ $<

clean:
	rm -f hw1 hw1-o0 hw1-o1 hw1-o2 hw1-o3 hw1-gprof hw1-debug gmon.out

