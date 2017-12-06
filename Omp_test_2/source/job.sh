#PBS -N job24
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=24
aprun -n 1 -d 24 ./hybrid > log24.txt
