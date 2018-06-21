#!/bin/sh

if [ -n "$1" ]; then
    while [ -z "$SCRIPT" ]
    do
        read -r -p "Type the shell script you want to run. (ex. *****.sh) : " SCRIPT
    done
    echo "$SCRIPT.sh"
    if [ $1 -eq 0 ]; then
        qsub $SCRIPT.sh
    else
        for i in `seq 1 $1`; do
            while [ -z "$JOBID" ]
            do
                read -r -p "Type a number to set the dependent job ID. (ex. *****.sdb) : " JOBID
            done
            #echo "$JOBID"
            qsub -W depend=afterok:$JOBID $SCRIPT.sh | tee tmp.txt
            JOBID=$(cat tmp.txt)
        done
    fi
else
    echo "Please set the first argument to decide how many times to execute the job."
fi

rm -f tmp.txt
