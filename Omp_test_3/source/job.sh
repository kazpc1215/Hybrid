#PBS -N Ntr1E4_t1E0yr_all_omp01
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Ntr1E4_t1E0yr_all_omp01.exe >> /work/isoyakz/Dynamical_Friction/log/Ntr1E4_t1E0yr_all_omp01.txt
