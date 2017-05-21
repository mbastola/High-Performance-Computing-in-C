#!/bin/bash
set -eu
time1=$(date +%s%3N)
make norm
time2=$(date +%s%3N)
echo $((time2 - time1))

