#include "pin.H"
#include <iostream>
#include <fstream>
#include "dmtcpaware.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

ofstream outFile;


VOID PrintName(RTN rtn)
{

    string name = RTN_Name(rtn);
    outFile<<"Routine Name: "<<name<<endl;

}

VOID instrument_routine(RTN rtn, void *ip)
{

    RTN_Open(rtn);
    INS ins1 = RTN_InsHead(rtn);
    INS_InsertCall(ins1, IPOINT_BEFORE, (AFUNPTR)PrintName, IARG_PTR, rtn, IARG_END);

    RTN_Close(rtn);

}

int main(int argc, char * argv[])
{
    outFile.open("trace_output.txt");
    // Initialize symbol table code, needed for rtn instrumentation
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    RTN_AddInstrumentFunction(instrument_routine, 0);
    PIN_StartProgram();
    outFile.close();
    return 0;
}
            

