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
VOID print_register_value(ADDRINT addr)
{
    //cout<<"reg value: "<<addr<<endl;
}

VOID instrument_instruction(INS ins)
{
    cout<<"NEW"<<endl;

        int opCount = INS_OperandCount(ins);
    cout<<"ins opcode: " <<INS_Opcode(ins)<<", mnemonic:"<<INS_Mnemonic(ins).c_str()<<" opCount: "<<opCount<<endl;
        //cout<<"instrumenting instruction: "<< INS_Mnemonic(ins).c_str()<<"in routine "<<routine<<endl;


        if(INS_IsMemoryRead(ins))
        {
            cout<<"instr is read"<<endl;
        }
        else if(INS_IsMemoryWrite(ins))
        {
            cout<<"instr is write"<<endl;

            for(int i = 0; i< opCount;i++)
            {
                if(INS_OperandRead(ins,i))
                {
                    cout<<"source is: "<<i<<" out of "<<opCount;
                    if(INS_OperandIsMemory(ins, i))
                    {
                        cout<<"memory"<<endl;
                    }
                    if(INS_OperandIsImmediate(ins, i))
                    {
                        cout<<"immediate"<<endl;
                    }
                    if(INS_OperandIsReg(ins, i))
                    {
                        cout<<"register ";
                        REG regist = INS_OperandReg(ins,i);
                        cout<<REG_StringShort(regist)<<endl;
                        if(REG_StringShort(regist) == "r13")
                        INS_InsertCall(ins,IPOINT_BEFORE, (AFUNPTR)print_register_value, IARG_REG_VALUE, REG_EAX, IARG_END);
                    }
                    if(INS_OperandIsFixedMemop(ins, i))
                    {
                        cout<<"fixed memop"<<endl;
                    }

                }
                if(INS_OperandWritten(ins,i))
                {
                    cout<<"destination is: "<<i<<" out of "<<opCount;

                    if(INS_OperandIsMemory(ins, i))
                    {
                        cout<<"memory"<<endl;
                    }
                    if(INS_OperandIsImmediate(ins, i))
                    {
                        cout<<"immediate"<<endl;
                    }
                    if(INS_OperandIsReg(ins, i))
                    {
                        cout<<"register"<<endl;
                    }
                    if(INS_OperandIsFixedMemop(ins, i))
                    {
                        cout<<"fixed memop"<<endl;
                    }
                }
            }
        }
}
// This function is called before every instruction is executed
VOID instrument_routine(RTN rtn, void *ip)
{
	string name = RTN_Name(rtn);
	if(name == "ivan")
	{
        /*
		int count;
		void *stack[50]; // can hold 50, adjust appropriately
		char **symbols;

		count = backtrace(stack, 50);
		symbols = backtrace_symbols(stack, count);

		for (int i = 0; i < count; i++)
			puts(symbols[i]);

		delete(symbols);

*/
        /*
		void *array[10];
		size_t size;

		// get void*'s for all entries on the stack
		size = backtrace(array, 10);
		//
		//     // print out all the frames to stderr
		//       fprintf(stderr, "Error: signal %d:\n", sig);
		backtrace_symbols_fd(array, size, 2);
*/

    RTN_Open(rtn);
		for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins))
		{
			// Insert a call to docount to increment the instruction counter for this rtn
			INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)instrument_instruction, IARG_PTR,ins, IARG_END);
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
