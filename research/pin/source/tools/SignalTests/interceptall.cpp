/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2012 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
/*
 * This test verifies that we can call PIN_InterceptSignal() and PIN_UnblockSignal()
 * for all signals.  Some signals can't be intercepted, and Pin used to crash if
 * we attempted to intercept those signals.
 */

#include <pin.H>
#include <signal.h>
#include <iostream>
#include<stdio.h>

#ifdef TARGET_BSD
 #ifndef SIGRTMIN
  #define SIGRTMIN 128
 #endif
#endif

#ifdef TARGET_MAC
 #ifndef SIGRTMIN
  #define SIGRTMIN 32
 #endif
#endif

ADDRINT mine;
static CONTEXT saved;

static BOOL Intercept(THREADID, INT32, CONTEXT *, BOOL, const EXCEPTION_INFO * ex, VOID *);
static VOID SysBefore(ADDRINT ip, ADDRINT num, ADDRINT arg0, ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5);

VOID SysBefore(ADDRINT ip,ADDRINT raddr, ADDRINT num, ADDRINT arg0, ADDRINT arg1, ADDRINT arg2, ADDRINT arg3, ADDRINT arg4, ADDRINT arg5)
{

    if(num == 1)
    {
        //mine = ip;
        printf("at ip: 0x%lx,at return address: %p, syscall: %ld(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
                (unsigned long)ip,
                raddr,
                (long)num,
                (unsigned long)arg0,
                (unsigned long)arg1,
                (unsigned long)arg2,
                (unsigned long)arg3,
                (unsigned long)arg4,
                (unsigned long)arg5);
    }
}


VOID SyscallEntry(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v)
{
    SysBefore(PIN_GetContextReg(ctxt, REG_INST_PTR),
PIN_GetContextReg(ctxt, LEVEL_BASE::REG_RSP),
            PIN_GetSyscallNumber(ctxt, std),
            PIN_GetSyscallArgument(ctxt, std, 0),
            PIN_GetSyscallArgument(ctxt, std, 1),
            PIN_GetSyscallArgument(ctxt, std, 2),
            PIN_GetSyscallArgument(ctxt, std, 3),
            PIN_GetSyscallArgument(ctxt, std, 4),
            PIN_GetSyscallArgument(ctxt, std, 5));
}

VOID GetReturnAddress(CONTEXT * context)
{
    cout<<"in get return address ";
    ADDRINT temp = PIN_GetContextReg(context, LEVEL_BASE::REG_RSP);
    mine = temp;
    printf("rsp: %p\n", temp);
    PIN_SaveContext(context,&saved);
}

VOID instrument_routine(RTN rtn, void *ip)
{
	string name = RTN_Name(rtn);
	if(name == "helloworld")
	{
        RTN_Open(rtn);
        INS ins = RTN_InsHead(rtn);
        INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(GetReturnAddress),IARG_CONTEXT,IARG_END);
        RTN_Close(rtn);

	}
}

int main(int argc, char **argv)
{

    PIN_InitSymbols();    
    PIN_Init(argc, argv);

    RTN_AddInstrumentFunction(instrument_routine, 0);
    
    for (int sig = 1;  sig < SIGRTMIN;  sig++)
    {
        PIN_InterceptSignal(sig, Intercept, 0);
        PIN_UnblockSignal(sig, TRUE);
    }

    PIN_AddSyscallEntryFunction(SyscallEntry,0);

    PIN_StartProgram();
    return 0;
}


static BOOL Intercept(THREADID, INT32 sig, CONTEXT * context, BOOL, const EXCEPTION_INFO * ex, VOID *)
{
    std::cerr << "Intercepted signal " << sig << std::endl;
    cout<<PIN_ExceptionToString(ex)<<endl;
    printf("rip:%p\n",PIN_GetContextReg(context, REG_INST_PTR));
    ADDRINT temp = PIN_GetContextReg(context, LEVEL_BASE::REG_RSP);
    printf("rsp: %p\n", temp);
    printf("mine: %p\n", mine);
    PIN_SetContextReg(context,REG_INST_PTR, mine );
    //PIN_ExecuteAt(&saved);
    context = &saved;
    return false;
}
