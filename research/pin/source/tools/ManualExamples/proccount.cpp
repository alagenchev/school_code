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

// Holds instruction count for a single procedure
typedef struct RtnCount
{
    string _name;
    string _image;
    ADDRINT _address;
    RTN _rtn;
    UINT64 _rtnCount;
    UINT64 _icount;
    struct RtnCount * _next;
} RTN_COUNT;

// Linked list of instruction counts for each routine
RTN_COUNT * RtnList = 0;
VOID print_register_value(INS ins, ADDRINT addr)
{
	cout<<"reg value: "<<*(int*)addr<<endl;
    //cout<<"reg value: "<<addr<<endl;
}

VOID instrument_instruction(INS ins)
{
	
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
VOID RecordMemRead(VOID * ip, VOID * addr)
{
	    printf("%p: addr: %p, R %d\n", ip,addr, *(((int *)addr)+1));
        if(*(int *)addr == 999)
        {
            *(int *)addr = 777;
        }
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

            if(INS_IsMemoryRead(ins))
            {

				for(int i = 0; i< opCount;i++)
                {
                    if(INS_MemoryOperandIsRead(ins,i))
                    {
                        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead,
                                IARG_INST_PTR,
                                IARG_MEMORYOP_EA, i,
                                IARG_END);
                    }
                }
            }

			if(INS_IsMemoryWrite(ins))
			{
				for(int i = 0; i< opCount;i++)
				{
					if(INS_OperandIsImmediate(ins,i))
					{
						cout<<"immediate "<<INS_OperandImmediate(ins,i)<<endl;
					}
					if(INS_MemoryOperandIsWritten(ins,i) && INS_HasFallThrough(ins))
                    {
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
                    }
					/*
					else if(INS_OperandRead(ins,i))
					{
						if(INS_OperandIsReg(ins, i))
						{
							cout<<"register ";
							REG regist = INS_OperandReg(ins,i);
							cout<<REG_StringShort(regist)<<endl;
							//if(REG_StringShort(regist) == "r13")
							//{
								//	print_register_value(ins, IARG_REG_VALUE, regist, IARG_END);
								INS_InsertCall(ins,IPOINT_BEFORE, (AFUNPTR)print_register_value, IARG_PTR, ins, IARG_REG_VALUE, regist, IARG_END);
								INS_InsertCall(ins,IPOINT_AFTER, (AFUNPTR)print_register_value, IARG_PTR, ins, IARG_REG_VALUE, regist, IARG_END);
							//}

						}
					}
					*/
				}
			}
			//		INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)instrument_instruction, IARG_PTR,ins, IARG_END);
		}
		RTN_Close(rtn);
	}
}
    


const char * StripPath(const char * path)
{
    const char * file = strrchr(path,'/');
    if (file)
        return file+1;
    else
        return path;
}

// Pin calls this function every time a new rtn is executed
VOID Routine(RTN rtn, VOID *v)
{
    
    // Allocate a counter for this routine
    RTN_COUNT * rc = new RTN_COUNT;

    // The RTN goes away when the image is unloaded, so save it now
    // because we need it in the fini
    rc->_name = RTN_Name(rtn);
    rc->_image = StripPath(IMG_Name(SEC_Img(RTN_Sec(rtn))).c_str());
    rc->_address = RTN_Address(rtn);
    rc->_icount = 0;
    rc->_rtnCount = 0;

    // Add to list of routines
    rc->_next = RtnList;
    RtnList = rc;
            
    RTN_Open(rtn);
            
    // Insert a call at the entry point of a routine to increment the call count
    RTN_InsertCall(rtn, IPOINT_BEFORE, (AFUNPTR)instrument_routine, IARG_PTR, rtn, IARG_END);
    
    /*
    // For each instruction of the routine
    for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins))
    {
        // Insert a call to docount to increment the instruction counter for this rtn
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)instrument_instruction, IARG_PTR,ins, IARG_END);
    }
*/
    
    RTN_Close(rtn);
}
INT32 Usage()
{
    cerr << "This Pintool counts the number of times a routine is executed" << endl;
    cerr << "and the number of instructions executed in a routine" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    // Initialize symbol table code, needed for rtn instrumentation
    PIN_InitSymbols();

    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    // Register Routine to be called to instrument rtn
    RTN_AddInstrumentFunction(instrument_routine, 0);

    PIN_StartProgram();
    
    return 0;
}
