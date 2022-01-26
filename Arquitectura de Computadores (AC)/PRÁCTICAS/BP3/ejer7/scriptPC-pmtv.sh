#!/bin/bash

export OMP_NUM_THREADS=8
N=15360

export OMP_SCHEDULE="STATIC"
echo "STATIC,deafault";
./pmtv-OpenMP $N

export OMP_SCHEDULE="STATIC,1"
echo "STATIC,1";
./pmtv-OpenMP $N

export OMP_SCHEDULE="STATIC,64"
echo "STATIC,64";
./pmtv-OpenMP $N

echo "--------------------------";

export OMP_SCHEDULE="DYNAMIC"
echo "DYNAMIC,default";
./pmtv-OpenMP $N

export OMP_SCHEDULE="DYNAMIC,1"
echo "DYNAMIC,1";
./pmtv-OpenMP $N

export OMP_SCHEDULE="DYNAMIC,64"
echo "DYNAMIC,64";
./pmtv-OpenMP $N

echo "--------------------------";

export OMP_SCHEDULE="GUIDED"
echo "GUIDED,default";
./pmtv-OpenMP $N

export OMP_SCHEDULE="GUIDED,1"
echo "GUIDED,1";
./pmtv-OpenMP $N

export OMP_SCHEDULE="GUIDED,64"
echo "GUIDED,64";
./pmtv-OpenMP $N
