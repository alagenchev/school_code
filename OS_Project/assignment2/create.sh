#!/bin/bash

g++ create_wrapper.cpp -o wrapper.out
./wrapper.out functions_ts.txt
gcc -g -Wall -shared -fPIC -o liboverride.so output.c -ldl -ldmtcpaware
