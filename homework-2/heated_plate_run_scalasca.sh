#!/bin/bash
#
#  Compile the program with gcc
#
export PATH=$PATH:/cluster/engine/scorep-1.2.3/bin/
export PATH=$PATH:/cluster/engine/scalasca-2.0/bin/
export PATH=$PATH:/home/warehouse/dshook/bin/

make scalasca
#
#
#  Run with 1, 2, and 4 threads. Change these values if you'd like.
#
echo "Run with 1 thread."
export OMP_NUM_THREADS=1
scalasca -analyze ./heated_plate > heated_plate_output.txt
#
echo "Run with 2 threads."
export OMP_NUM_THREADS=2
scalasca -analyze ./heated_plate >> heated_plate_output.txt
#
echo "Run with 4 threads."
export OMP_NUM_THREADS=4
scalasca -analyze ./heated_plate >> heated_plate_output.txt
#
#  Discard the executable file.
#
make clean
#
echo "Program output written to heated_plate_output.txt"
