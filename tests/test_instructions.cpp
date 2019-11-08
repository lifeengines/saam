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
    std::string in;
    std::string out;
    std::ifstream inputFile("tests/sample-snippet/data-processing.s");
    std::ifstream expOutputFile("tests/tests-output/test-data-processing.txt");
    
    ErrorQueue q = ErrorQueue();
    std::vector<Instruction *> v;

    if (!inputFile.is_open() || !expOutputFile.is_open()) {
        std::cerr << "Unable to open tests files.\n";
        return EXIT_FAILURE; 
    }

    /* Fetch instruction from test input file */
    while (getline(inputFile, in)) {
        std::smatch sm;
        LINE_TYPE type = getLineType(in, sm);

        switch (type) {
            case DATAPROC_REG_OP2: {
                Instruction *ins = createDataProcRegOp2(sm, 0, 0, q);
                if (ins) v.push_back(ins);
                break;
            }

            default:
                break;
        }
    }

    /* Compare result with expected output */
    for (size_t i = 0; i < v.size(); i++) {
        if (getline(expOutputFile, out)) {
            std::string status = 
                (v[i]->printInstructionString() == out) ? "PASS" : "FAIL";
            std::cout << "Testing instruction '"
                        << v[i]->printInstructionString() << "': " << status
                        << "\n";
        }
        else {
            std::cerr << "ERR: Expected output file length doesn't match\n";
        }
        delete v[i];
        v[i] = NULL;
    }

    inputFile.close();
    expOutputFile.close();

    return 0;
}