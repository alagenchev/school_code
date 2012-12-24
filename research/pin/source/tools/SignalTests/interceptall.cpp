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

static CONTEXT saved_context;

static BOOL Intercept(THREADID, INT32, CONTEXT *, BOOL, const EXCEPTION_INFO * ex, VOID *);

VOID PrintContext(const CONTEXT * ctxt);

VOID GetCheckpoint(CONTEXT * context)
{
    cout<<"saving checkpoint"<<endl;

    PrintContext(context);
    PIN_SaveContext(context,&saved_context);
}

ADDRINT mine;

VOID PrintContext(const CONTEXT * ctxt)
{
    cout << "ip:    " <<hex<< PIN_GetContextReg( ctxt, REG_INST_PTR ) << endl;
    cout << "gax:   " << hex<< PIN_GetContextReg( ctxt, REG_GAX )<<dec << endl;
    cout << "gbx:   " << hex<< PIN_GetContextReg( ctxt, REG_GBX ) <<dec<< endl;
    cout << "gcx:   " << hex<< PIN_GetContextReg( ctxt, REG_GCX ) <<dec<< endl;
    cout << "gdx:   " << hex<< PIN_GetContextReg( ctxt, REG_GDX ) <<dec<< endl;
    cout << "gsi:   " << hex<< PIN_GetContextReg( ctxt, REG_GSI ) <<dec<< endl;
    cout << "gdi:   " << hex<< PIN_GetContextReg( ctxt, REG_GDI ) <<dec<< endl;
    cout << "gbp:   " << hex<< PIN_GetContextReg( ctxt, REG_GBP ) <<dec<< endl;
    cout << "sp:    " << hex<< PIN_GetContextReg( ctxt, REG_STACK_PTR ) <<dec<< endl;

    cout << "ss:    " << hex<< PIN_GetContextReg( ctxt, REG_SEG_SS ) <<dec<< endl;
    cout << "cs:    " << hex<< PIN_GetContextReg( ctxt, REG_SEG_CS ) <<dec<< endl;
    cout << "ds:    " << hex<< PIN_GetContextReg( ctxt, REG_SEG_DS ) <<dec<< endl;
    cout << "es:    " << hex<< PIN_GetContextReg( ctxt, REG_SEG_ES ) <<dec<< endl;
    cout << "fs:    " << hex<< PIN_GetContextReg( ctxt, REG_SEG_FS ) <<dec<< endl;
    cout << "gs:    " << hex<< PIN_GetContextReg( ctxt, REG_SEG_GS ) <<dec<< endl;
    cout << "gflags:" << hex<< PIN_GetContextReg( ctxt, REG_GFLAGS ) <<dec<< endl;
    cout << endl;
}

VOID Before(CONTEXT * ctxt)
{
    ADDRINT BeforeIP = (ADDRINT)PIN_GetContextReg( ctxt, REG_INST_PTR);
    cout << "Before: IP = " << hex << BeforeIP << dec << endl;
    //PrintContext(ctxt);
    /*
       ADDRINT BeforeIP = (ADDRINT)PIN_GetContextReg( ctxt, REG_INST_PTR);
       ADDRINT BeforeRBP = (ADDRINT)PIN_GetContextReg( ctxt, REG_EBP_PTR);
       ADDRINT BeforeRSP = (ADDRINT)PIN_GetContextReg( ctxt, REG_STACK_PTR);
       mine = BeforeIP;
       cout << "Before: IP = " << hex << BeforeIP << dec << endl;
       cout << "Before: RBP = " << hex << BeforeRBP << dec << endl;
       cout << "Before: RSP = " << hex << BeforeRSP << dec << endl;
       */
}

VOID instrument_routine(RTN rtn, void *ip)
{
    string name = RTN_Name(rtn);
    RTN_Open(rtn);
    INS ins = RTN_InsHead(rtn);
    if(name == "helloworld")
    {

        /*
           const UINT32 max_r = INS_MaxNumRRegs(ins);

           for( UINT32 i=0; i < max_r; i++ )
           {
           const REG reg =  INS_RegR(ins, i );
           if( REG_is_gr(reg) )
           {
           cout<<"read register: "<<REG_StringShort(reg)<<" "<<REG_FullRegName(reg)
           <<", val: "<<""<<endl;
           }
           }

           const UINT32 max_w = INS_MaxNumWRegs(ins);            

           for( UINT32 i=0; i < max_w; i++ )
           {
           const REG reg =  INS_RegW(ins, i );
           if( REG_is_gr(reg) )
           {

           cout<<"write register: "<<REG_StringShort(reg)<<" "<<REG_FullRegName(reg)
           <<", val: "<<""<<endl;
           }
           }
           */
        INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(GetCheckpoint),IARG_CONTEXT,IARG_END);

    }

     //   INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(Before),IARG_CONTEXT,IARG_END);

    RTN_Close(rtn);

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

    PIN_StartProgram();
    return 0;
}


static BOOL Intercept(THREADID, INT32 sig, CONTEXT * context, BOOL, const EXCEPTION_INFO * ex, VOID *)
{
    //PIN_ExecuteAt(&saved);
    //context = &saved_context;
    std::cerr << "Intercepted signal " << sig << std::endl;
    cout<<PIN_ExceptionToString(ex)<<endl;
    //printf("rip:%p\n",PIN_GetContextReg(context, REG_INST_PTR));
 //   PIN_SetContextReg(context,REG_INST_PTR, mine);
 //

    //cout<<"register: "<<REG_FullRegName(REG_INST_PTR)<<endl;
    /*
    for(int i = 0; i < REG_LAST; i++)
    {
    }
    */


    cout<<"before setting:"<<endl;
    PrintContext(context);
    ADDRINT temp = PIN_GetContextReg(&saved_context, REG_INST_PTR );
    PIN_SetContextReg(context,REG_INST_PTR, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GAX );
    PIN_SetContextReg(context,REG_GAX, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GBX );
    PIN_SetContextReg(context,REG_GBX, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GCX );
    PIN_SetContextReg(context,REG_GCX, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GDX );
    PIN_SetContextReg(context,REG_GDX, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GSI );
    PIN_SetContextReg(context,REG_GSI, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GDI );
    PIN_SetContextReg(context,REG_GDI, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GBP );
    PIN_SetContextReg(context,REG_GBP, temp);

    temp = PIN_GetContextReg(&saved_context, REG_STACK_PTR );
    PIN_SetContextReg(context,REG_STACK_PTR, temp);

    temp = PIN_GetContextReg(&saved_context, REG_SEG_SS );
    PIN_SetContextReg(context,REG_SEG_SS, temp);

    temp = PIN_GetContextReg(&saved_context, REG_SEG_CS );
    PIN_SetContextReg(context,REG_SEG_CS, temp);

    temp = PIN_GetContextReg(&saved_context, REG_SEG_DS );
    PIN_SetContextReg(context,REG_SEG_DS, temp);

    temp = PIN_GetContextReg(&saved_context, REG_SEG_ES );
    PIN_SetContextReg(context,REG_SEG_ES, temp);

    temp = PIN_GetContextReg(&saved_context, REG_SEG_FS );
    PIN_SetContextReg(context,REG_SEG_FS, temp);

    temp = PIN_GetContextReg(&saved_context, REG_SEG_GS );
    PIN_SetContextReg(context,REG_SEG_GS, temp);

    temp = PIN_GetContextReg(&saved_context, REG_GFLAGS );
    PIN_SetContextReg(context,REG_GFLAGS, temp);

    cout<<"after setting:"<<endl;
    PrintContext(context);
    return false;
}
