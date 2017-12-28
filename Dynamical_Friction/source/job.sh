#PBS -N job01
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export OMP_WAIT_POLICY=PASSIVE
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Ntr1E3_t2E0yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand1.exe >> /work/isoyakz/Dynamical_Friction/log/Ntr1E3_t2E0yr_dt1yr_Mtot3E-5_ecc1E-2_inc5E-3_rand1.txt
