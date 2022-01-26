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


export OMP_NUM_THREADS=12
N=15360

export OMP_SCHEDULE="STATIC"
echo "STATIC,default";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

export OMP_SCHEDULE="STATIC,1"
echo "STATIC,1";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

export OMP_SCHEDULE="STATIC,64"
echo "STATIC,64";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

echo "--------------------------";

export OMP_SCHEDULE="DYNAMIC"
echo "DYNAMIC,default";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

export OMP_SCHEDULE="DYNAMIC,1"
echo "DYNAMIC,1";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

export OMP_SCHEDULE="DYNAMIC,64"
echo "DYNAMIC,64";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

echo "--------------------------";

export OMP_SCHEDULE="GUIDED"
echo "GUIDED,default";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

export OMP_SCHEDULE="GUIDED,1"
echo "GUIDED,1";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N

export OMP_SCHEDULE="GUIDED,64"
echo "GUIDED,64";
srun -p ac ./pmtv-OpenMP $N
srun -p ac ./pmtv-OpenMP $N
