#!/bin/bash

export OMP_NUM_THREADS=1
echo "1 PROCESADOR";
N=100
echo "TAMA = 100";
./pmm-OpenMP $N

N=500
echo "TAMA = 500";
./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
./pmm-OpenMP $N

N=1500
echo "TAMA = 1500";
./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=2
echo "2 PROCESADOR";
N=100
echo "TAMA = 100";
./pmm-OpenMP $N

N=500
echo "TAMA = 500";
./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
./pmm-OpenMP $N

N=1500
echo "TAMA = 1500";
./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=3
echo "3 PROCESADOR";
N=100
echo "TAMA = 100";
./pmm-OpenMP $N

N=500
echo "TAMA = 500";
./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
./pmm-OpenMP $N

N=1500
echo "TAMA = 1500";
./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=4
echo "4 PROCESADOR";
N=100
echo "TAMA = 100";
./pmm-OpenMP $N

N=500
echo "TAMA = 500";
./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
./pmm-OpenMP $N

N=1500
echo "TAMA = 1500";
./pmm-OpenMP $N
