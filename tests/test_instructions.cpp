/*------------------------------------------------------------------------
 *
 *  Small ARM Assembler Module
 *  
 *  Copyright (c) 2019 - Trung Truong
 *  All rights reserved.
 *  Permission is hereby granted, free of charge, to any person 
 *  obtaining a copy of this software and associated documentation 
 *  files (the "Software"), to deal in the Software without restriction,
 *  including without limitation the rights to use, copy, modify, merge,
 *  publish, distribute, sublicense, and/or sell copies of the Software,
 *  and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included 
 *  in all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 *  File name: test_instructions.cpp
 *
 *  Description: Test driver for Instruction class
 * 
 -----------------------------------------------------------------------*/

#define _INSTRUCTION_DEBUG_
#include <assert.h>
#include "../src/parser.h"

using namespace std;

int main () {
    string line;
    ifstream file ("tests/sample-snippet/data-processing.s");
    ErrorQueue q = ErrorQueue();

    if (file.is_open()) {
        while (getline(file, line)) {
            // cout << line << '\n';
            std::pair<LINE_TYPE, std::smatch> match = getLineType(line);
            if (match.first == DATAPROC_REG_OP2) {
                DataProc *ins = createDataProcRegOp2(match.second, 0, 0, q);
                cout << "Hello" << ins->getInstructionString() << endl;
                delete ins;
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open file\n"; 
    }
    return 0;
}