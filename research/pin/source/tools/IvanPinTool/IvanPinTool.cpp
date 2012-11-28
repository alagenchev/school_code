#include "pin.H"
#include <iostream>
#include <fstream>
#include "dmtcpaware.h"

FILE * trace;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE,  "pintool",
    "o", "", "specify file name for MyPinTool output");

INT32 Usage()
{
    cerr << KNOB_BASE::StringKnobSummary() << endl;

    return -1;
}
 // Print syscall number and arguments
VOID SysBefore(ADDRINT ip, ADDRINT num, ADDRINT arg0, ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5)
{
#if defined(TARGET_LINUX) && defined(TARGET_IA32) 
    // On ia32 Linux, there are only 5 registers for passing system call arguments, 
    //     // but mmap needs 6. For mmap on ia32, the first argument to the system call 
    //         // is a pointer to an array of the 6 arguments
    if (num == SYS_mmap)
    {
        ADDRINT * mmapArgs = reinterpret_cast<ADDRINT *>(arg0);
        arg0 = mmapArgs[0];
        arg1 = mmapArgs[1];
        arg2 = mmapArgs[2];
        arg3 = mmapArgs[3];
        arg4 = mmapArgs[4];
        arg5 = mmapArgs[5];
    }
#endif

    if(num == 1)
    {
        if(dmtcpIsEnabled())
        {
            cout<<"dmtcp is enabled"<<endl;
        }
        else
        {
            cout<<"dmtcp not enabled"<<endl;
        }

        fprintf(trace,"at ip: 0x%lx, syscall: %ld(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
                (unsigned long)ip,
                (long)num,
                (unsigned long)arg0,
                (unsigned long)arg1,
                (unsigned long)arg2,
                (unsigned long)arg3,
                (unsigned long)arg4,
                (unsigned long)arg5);
        fflush(trace);
    }
}
VOID SyscallEntry(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v)
{
    SysBefore(PIN_GetContextReg(ctxt, REG_INST_PTR),
            PIN_GetSyscallNumber(ctxt, std),
            PIN_GetSyscallArgument(ctxt, std, 0),
            PIN_GetSyscallArgument(ctxt, std, 1),
            PIN_GetSyscallArgument(ctxt, std, 2),
            PIN_GetSyscallArgument(ctxt, std, 3),
            PIN_GetSyscallArgument(ctxt, std, 4),
            PIN_GetSyscallArgument(ctxt, std, 5));
}

int main(int argc, char *argv[])
{
    
    PIN_InitSymbols();

    // Initialize PIN library. Print help message if -h(elp) is specified
    // in the command line or the command line is invalid 
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    

    string fileName = KnobOutputFile.Value();

    if (!fileName.empty()) 
    { 
        trace = fopen(fileName.c_str(), "w");
    }
    else
    {

        cerr <<  "===============================================" << endl;
        printf("YOU need to specify output file name using -o\n");
        Usage();
        return -1;
    }

        PIN_AddSyscallEntryFunction(SyscallEntry,0);
   cerr <<  "===============================================" << endl;
    cerr <<  "This application is instrumented by MyPinTool" << endl;
    if (!KnobOutputFile.Value().empty()) 
    {
        cerr << "See file " << KnobOutputFile.Value() << " for analysis results" << endl;
    }
    cerr <<  "===============================================" << endl;

    // Start the program, never returns
    //

    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
