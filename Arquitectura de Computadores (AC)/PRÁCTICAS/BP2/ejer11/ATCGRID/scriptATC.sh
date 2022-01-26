#!/bin/bash

export OMP_NUM_THREADS=1
for (( i = 10000; i <= 30000; i += 1000 )); do
    srun -p ac ./pmv-OpenMP-a $i >> tiempos-a-1h.dat
done

export OMP_NUM_THREADS=4
for (( i = 10000; i <= 30000; i += 1000 )); do
    srun -p ac ./pmv-OpenMP-a $i >> tiempos-a-4h.dat
done

export OMP_NUM_THREADS=8
for (( i = 10000; i <= 30000; i += 1000 )); do
    srun -p ac ./pmv-OpenMP-a $i >> tiempos-a-8h.dat
done

export OMP_NUM_THREADS=12
for (( i = 10000; i <= 30000; i += 1000 )); do
    srun -p ac ./pmv-OpenMP-a $i >> tiempos-a-12h.dat
done
