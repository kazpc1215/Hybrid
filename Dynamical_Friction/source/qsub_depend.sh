#!/bin/sh

while [ -z $SCRIPT ]
do
    read -r -p "Type the shell script name you want to run. (ex. *****.sh) : " SCRIPT
done
echo "$SCRIPT"

while [ -z $YESNO ]
do
    read -r -p "Is there a dependent job? (y / n) : " YESNO
done
echo "$YESNO"

if [ $YESNO = 'y' ] ; then
    
    while [ -z $JOBID ]
    do
        read -r -p "Type a number to set the dependent job ID. (ex. *****.sdb) : " JOBID
    done
    echo "$JOBID"
    
    while [ -z $NRUN ]
    do
	read -r -p "Type a number to decide how many times to execute the job.: " NRUN
    done
    echo "$NRUN"
    
    for i in `seq 1 $NRUN` ; do
        qsub -W depend=afterok:$JOBID $SCRIPT.sh | tee tmp.txt
        JOBID=$(cat tmp.txt)
        echo ""
        echo "-----dependency of $JOBID-----"
        qstat -f $JOBID | grep depend
        echo -n "------------------------"
	for n in `seq 1 ${#JOBID}` ; do
            echo -n "-"
        done
        echo ""
	echo ""
    done
    
elif [ $YESNO = 'n' ] ; then

    while [ -z $NRUN ]
    do
        read -r -p "Type a number to decide how many times to execute the job.: " NRUN
    done
    echo "$NRUN"
    
    for i in `seq 1 $NRUN` ; do
	if [ $i = 1 ] ; then
	    qsub $SCRIPT.sh | tee tmp.txt
	else
	    qsub -W depend=afterok:$JOBID $SCRIPT.sh | tee tmp.txt
	fi
        JOBID=$(cat tmp.txt)
	echo ""
        echo "-----dependency of $JOBID-----"
        qstat -f $JOBID | grep depend
        echo -n "------------------------"
	for n in `seq 1 ${#JOBID}` ; do
	    echo -n "-"
	done
	echo ""
	echo ""
    done

else
	    
    echo "Input 'y' or 'n'."
    
fi

rm -f tmp.txt
