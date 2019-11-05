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
 *  File name: instruction.cpp
 *
 *  Description: Function definitions for Instruction class
 *  See individual description for more details.
 * 
 -----------------------------------------------------------------------*/

#include "all.h"
#include "instruction.h"

Instruction::Instruction(MNEMONIC m, uint32_t offset, CONDITION c) {
    mnemonic    = m;
    memOffset   = offset;
    cond        = c;
};

Instruction::~Instruction() {};

uint32_t Instruction::getMemOffset() {
    return memOffset;
};

void Instruction::setMemOffset(uint32_t offset) {
    memOffset = offset;
};

DataProc::DataProc  (MNEMONIC m, uint32_t offset, CONDITION c,
                    REGISTER _rn, REGISTER _rd, regOperand2 &_regOp)
                    : Instruction(m, offset, c) { 
    operand2.regOp = _regOp;
    rn             = _rn;
    rd             = _rd;
    immOperand     = 0;                      
};

DataProc::DataProc  (MNEMONIC m, uint32_t offset, CONDITION c,
                    REGISTER _rn, REGISTER _rd, immOperand2 &_immOp)
                    : Instruction(m, offset, c) {                       
    operand2.immOp = _immOp;
    rn             = _rn;
    rd             = _rd;
    immOperand     = 1;   
};

DataProc::~DataProc() {};
