#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Enter the program's name along with parameters."
	exit 1
fi

echo "Running program $1"

export LD_PRELOAD="$PWD/liboverride.so"

$1 "${@:2}"
result=$?

export LD_PRELOAD=""

exit $result
