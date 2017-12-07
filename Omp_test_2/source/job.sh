#PBS -N job24
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=24
export OMP_WAIT_POLICY=PASSIVE
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d 24 ./hybrid > log24.txt
