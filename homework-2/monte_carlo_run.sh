#!/bin/bash
set -eu

make monte_carlo
: > monte_carlo_output.txt

for threads in 1 2 4 8 16 32; do
  echo "Run with $threads thread(s)."
  OMP_NUM_THREADS=$threads ./monte_carlo >> monte_carlo_output.txt
done

echo "Program output written to monte_carlo_output.txt"
