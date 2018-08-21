#PBS -N testjob
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_drmin2E-3_dthetamin0.125pi.exe >> /work/isoyakz/Dynamical_Friction/log/Ntr3E3_t1E2_dtlog_Mtot3E-5_Mmax5E-18_ecc1E-2_frag_drmin2E-3_dthetamin0.125pi.txt
