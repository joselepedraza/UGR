#!/bin/bash

#N entre 20000 y 100000
export OMP_NUM_THREADS=1
for (( i = 20000; i <= 60000; i += 1000 )); do
    ./pmv-OpenMP-a $i >> tiempos-a_1hebra_nalto.dat
done


export OMP_NUM_THREADS=4
for (( i = 20000; i <= 60000; i += 1000 )); do
    ./pmv-OpenMP-a $i >> tiempos-a_4hebras_nalto.dat
done


export OMP_NUM_THREADS=8
for (( i = 20000; i <= 60000; i += 1000 )); do
    ./pmv-OpenMP-a $i >> tiempos-a_8hebras_nalto.dat
done

#N entre 5000 y 20000
export OMP_NUM_THREADS=1
for (( i = 5000; i <= 20000; i += 1000 )); do
    ./pmv-OpenMP-a $i >> tiempos-a_1hebra_nbajo.dat
done


export OMP_NUM_THREADS=4
for (( i = 5000; i <= 20000; i += 1000 )); do
    ./pmv-OpenMP-a $i >> tiempos-a_4hebras_nbajo.dat
done


export OMP_NUM_THREADS=8
for (( i = 5000; i <= 20000; i += 1000 )); do
    ./pmv-OpenMP-a $i >> tiempos-a_8hebras_nbajo.dat
done

