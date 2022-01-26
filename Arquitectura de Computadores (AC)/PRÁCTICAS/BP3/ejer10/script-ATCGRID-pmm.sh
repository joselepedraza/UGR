#!/bin/bash

#sbatch -p ac -n1 --cpus-per-task=12 --hint=nomultithread --exclusive scriptATCGRID-pmtv.sh

#Órdenes para el sistema de colas:
#1. Asigna al trabajo un nombre
#SBATCH --job-name=pmv-OpenMP-a
#2. Asignar el trabajo a una cola (partición)
#SBATCH --partition=ac
#2. Asignar el trabajo a un account
#SBATCH --account=ac
#Obtener información de las variables del entorno del sistema de colas:

echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script):
$SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Nodo que ejecuta este trabajo:$SLURM_SUBMIT_HOST"
echo "No de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"

export OMP_NUM_THREADS=1
echo "1 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=2
echo "2 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=3
echo "3 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=4
echo "4 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=5
echo "5 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=6
echo "6 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=7
echo "7 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=8
echo "8 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=9
echo "9 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=10
echo "10 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=11
echo "11 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N

echo "--------------------------"

export OMP_NUM_THREADS=12
echo "12 PROCESADOR";
N=100
echo "TAMA = 100";
srun -p ac ./pmm-OpenMP $N

N=500
echo "TAMA = 500";
srun -p ac ./pmm-OpenMP $N

N=1000
echo "TAMA = 1000";
srun -p ac ./pmm-OpenMP $N
