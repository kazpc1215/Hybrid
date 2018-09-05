#PBS -N test
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_adjust_frag_dr2E-3_dtheta0.125pi.exe >> /work/isoyakz/Dynamical_Friction/log/Nc1E3_t1E2_dtlog_Mtot3E-5_Mmax5E-15_ecc3E-2_adjust_frag_dr2E-3_dtheta0.125pi.txt
