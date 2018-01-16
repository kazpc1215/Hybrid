#PBS -N job01
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=2
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Ntr1E2_t2E1yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand1.exe >> /work/isoyakz/Dynamical_Friction/log/Ntr1E2_t2E1yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_all_rand1.txt
