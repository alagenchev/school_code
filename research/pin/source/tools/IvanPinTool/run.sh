#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Enter the program's name."
	exit 1
fi

exec 2> /dev/null

#Note that command should exist.
dmtcp_checkpoint $PWD/$1 2> /dev/null
status=$?

while [ true ]; do
	if [ $status -eq 0 ]; then
		break;
	else
		echo "HELPER: Error. Reloading last checkpoint. Retry input."
		bash $PWD/dmtcp_restart_script.sh 2> /dev/null
		status=$?
	fi
done

rm dmtcp_restart*
rm ckpt*
