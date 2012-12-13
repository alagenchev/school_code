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
//
// This tool counts the number of times a routine is executed and 
// the number of instructions executed in a routine
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include "pin.H"
#include <execinfo.h>

ofstream outFile;

REG GetScratchReg(UINT32 index);
ADDRINT GetMemAddress(ADDRINT ea);
ADDRINT GetMemAddress2(ADDRINT ea);

VOID print_register_value(INS ins, ADDRINT addr)
{
	cout<<"reg value: "<<*(int*)addr<<endl;
    //cout<<"reg value: "<<addr<<endl;
}

VOID RecordMemWrite(VOID * ip, VOID * addr)
{
	    printf("%p: addr: %p, W %d\n", ip,addr, *(int *)addr);
        if(*(int *)addr == 666)
        {
        cout<<"will write"<<endl;
           *(((int *)addr)+1) = 999;
           cout<<"wrote"<<endl;
        }
}

VOID RecordMemRead(INS ins, VOID * ip, VOID * addr)
{

    cout<<"opcode:"<<INS_Opcode(ins)<<", mnemonic: "<<INS_Mnemonic(ins)<<endl;
    printf("%p: addr: %p, R %d\n", ip,addr, *(((int *)addr)+1));
    /*if(*(int *)addr == 666)
    {
        cout<<"replacing"<<endl;
        *(int *)addr = 777;
    }*/
}

// This function is called before every instruction is executed
VOID instrument_routine(RTN rtn, void *ip)
{
	string name = RTN_Name(rtn);
	if(name == "ivan")
	{
		RTN_Open(rtn);
		for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins))
		{
			int opCount = INS_OperandCount(ins);

                int opcode = INS_Opcode(ins);
            if(INS_IsMemoryRead(ins))
            {


                for(int i = 0; i< opCount;i++)
                {
                    if(INS_MemoryOperandIsRead(ins,i))
                    {
                        /*
                           INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead,IARG_PTR,ins,
                           IARG_INST_PTR,
                           IARG_MEMORYOP_EA, i,
                           IARG_END);
                           */

                        cout<<"opcode:"<<INS_Opcode(ins)<<", mnemonic: "<<INS_Mnemonic(ins)<<endl;
                        if(INS_Opcode(ins)!= XED_ICLASS_RET_NEAR)
                        {
                            REG scratchReg = GetScratchReg(i);
                            INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(GetMemAddress), 
                                    IARG_MEMORYOP_EA, i, IARG_RETURN_REGS, scratchReg, IARG_END);

                            INS_RewriteMemoryOperand(ins, i, scratchReg);
                        }
                    }
                }
            }

			if(INS_IsMemoryWrite(ins))
			{
				for(int i = 0; i< opCount;i++)
				{
                    /*
					if(INS_OperandIsImmediate(ins,i))
					{
						cout<<"immediate "<<INS_OperandImmediate(ins,i)<<endl;
					}
                    */
					if(INS_MemoryOperandIsWritten(ins,i) && INS_HasFallThrough(ins))
                    {

                        /*
                        INS_InsertCall(
                                ins, IPOINT_BEFORE, (AFUNPTR)RecordMemWrite,
                                IARG_INST_PTR,
                                IARG_MEMORYOP_EA, i,
                                IARG_END);

                        INS_InsertCall(
                                ins, IPOINT_AFTER, (AFUNPTR)RecordMemWrite,
                                IARG_INST_PTR,
                                IARG_MEMORYOP_EA, i,
                                IARG_END);
                                */

                        if(opcode != XED_ICLASS_PUSH)
                        {
                            REG scratchReg = GetScratchReg(i);
                            INS_InsertCall(ins, IPOINT_BEFORE, AFUNPTR(GetMemAddress), 
                                    IARG_MEMORYOP_EA, i, IARG_RETURN_REGS, scratchReg, IARG_END);

                            INS_RewriteMemoryOperand(ins, i, scratchReg);
                        }

                    }
				}
			}
		}
		RTN_Close(rtn);
	}
}
    
REG GetScratchReg(UINT32 index)
{
    static std::vector<REG> regs;

    while (index >= regs.size())
    {
        REG reg = PIN_ClaimToolRegister();
        if (reg == REG_INVALID())
        {
            std::cerr << "*** Ran out of tool registers" << std::endl;
            PIN_ExitProcess(1);
            /* does not return */
        }
        regs.push_back(reg);
    }

    return regs[index];
}

ADDRINT GetMemAddress2(ADDRINT ea)
{
    return ea;
}

ADDRINT GetMemAddress(ADDRINT ea)
{
    ea++;
    return ea;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize symbol table code, needed for rtn instrumentation
    PIN_InitSymbols();
    PIN_Init(argc, argv);
    RTN_AddInstrumentFunction(instrument_routine, 0);
    PIN_StartProgram();
    return 0;
}
