#!/bin/bash

export LD_PRELOAD=""
gcc -shared -fPIC -o liboverride.so override.c -ldl -ldmtcpaware
gcc main.c -o main.out
export LD_PRELOAD=$PWD/liboverride.so

