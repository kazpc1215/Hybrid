#PBS -N job01
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./N20_t1E8yr_dtlog_10RHM_ecc1E-2_inc5E-3_rand1.exe >> /work/isoyakz/Dynamical_Friction/log/N20_t1E8yr_dtlog_10RHM_ecc1E-2_inc5E-3_rand1.txt
