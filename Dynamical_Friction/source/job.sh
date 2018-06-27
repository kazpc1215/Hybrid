#PBS -N test
#PBS -l mppwidth=24
#PBS -j oe
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=1
export CRAY_OMP_CHECK_AFFINITY=TRUE
aprun -n 1 -d $OMP_NUM_THREADS ./Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-15_SEP5_ecc1E-2_frag_acc.exe >> /work/isoyakz/Dynamical_Friction/log/Ntr3E3_t1E3_dtlog_Mtot3E-5_Mmax5E-15_SEP5_ecc1E-2_frag_acc.txt
