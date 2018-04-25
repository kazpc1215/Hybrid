#PBS -N test
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./test_t1E3yr_dt1yr_e01_i005_frag.exe >> /work/isoyakz/Dynamical_Friction/log/test_t1E3yr_dt1yr_e01_i005_frag.txt
