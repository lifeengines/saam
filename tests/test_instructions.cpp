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

int main () {
    std::string line;
    std::ifstream file ("tests/sample-snippet/data-processing.s");
    ErrorQueue q = ErrorQueue();
    std::vector<Instruction *> v;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::smatch sm;
            LINE_TYPE type = getLineType(line, sm);

            if (type == DATAPROC_REG_OP2) {
                Instruction *ins = createDataProcRegOp2(sm, 0, 0, q);
                // std::cout << ins->printInstructionString() << std::endl;
                v.push_back(ins);
                // ins = NULL;
            }
        }

        for (size_t i = 0; i < v.size(); i++) {
            std::cout << v[i]->printInstructionString() << std::endl;
            delete v[i];
            v[i] = NULL;
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file\n"; 
    }
    return 0;
}