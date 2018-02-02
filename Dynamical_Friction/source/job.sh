#PBS -N job01
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1.exe >> /work/isoyakz/Dynamical_Friction/log/Ntr3E3_t1E4yr_dt1yr_Mtot3E-5_ecc1E-1_inc5E-2_rand1.txt
