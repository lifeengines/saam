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
 *  File name: error.cpp
 *
 *  Description: Function definitions for error module
 * 
 -----------------------------------------------------------------------*/
#include "error.h"

ErrorQueue::ErrorQueue() {};

ErrorQueue::~ErrorQueue() {};

void ErrorQueue::printErrors() {
    while (!q.empty()) {
        Error e = q.front();
        switch (e.type) {
            case INVALID_TOKEN: {
                std::cerr << "Line " << e.line << 
                ": ERR_INVALID_TOKEN: " << e.message << "\n";
                break;
            }
            case INVALID_VALUE: {
                std::cerr << "Line " << e.line << 
                ": ERR_INVALID_VALUE: " << e.message << "\n";
                break;
            }
            case OUT_OF_RANGE_VALUE: {
                std::cerr << "Line " << e.line << 
                ": ERR_OUT_OF_RANGE_VALUE: " << e.message << "\n";
                break;
            }
            case INVALID_SYNTAX: {
                std::cerr << "Line " << e.line << 
                ": ERR_INVALID_SYNTAX: " << e.message << "\n";
                break;
            }
            case ILL_FORMAT_INSTRUCTION: {
                std::cerr << "Line " << e.line << 
                ": ILL_FORMAT_INSTRUCTION: " << e.message << "\n";
                break;
            }
            default: {
                break;
            }
        }
        q.pop();
    }
};

bool ErrorQueue::addError(Error &e) {
    try {
        q.push(e);
        return true;
    }
    catch (std::bad_alloc) {
        std::cerr << "ERR_BAD_ALLOC: Failed to add error" << "\n";
        return false;
    }
};
