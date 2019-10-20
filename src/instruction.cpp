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

Instruction::Instruction(MNEMONIC m, uint32_t offset) {
    mnemonic = m;
    memOffset = offset;
    tlInstructionPtr = NULL;
}

Instruction::~Instruction() {}

void Instruction::setTlInstructionPtr(Instruction *tl) {
    tlInstructionPtr = tl;
}

void Instruction::setCondition(uint8_t condition) {
    cond = condition;
}

void Instruction::dataProcReg(uint8_t rn, uint8_t rd, uint8_t rm, uint8_t sh) {
    body.dataProcessing.rn = rn;
    body.dataProcessing.rd = rd;
    body.dataProcessing.operand2.reg.rm = rm;
    body.dataProcessing.operand2.reg.shift = sh;
}

void Instruction::dataProcImm(uint8_t rn, uint8_t rd, uint8_t ro, uint8_t im) {
    body.dataProcessing.rn = rn;
    body.dataProcessing.rd = rd;
    body.dataProcessing.operand2.imm.rotate = ro;
    body.dataProcessing.operand2.imm.imm = im;
}

void Instruction::singleDataTransfer(uint8_t rn, uint8_t rd, uint16_t offset) {
    body.singleDataTransfer.rn = rn;
    body.singleDataTransfer.rd = rd;
    body.singleDataTransfer.offset = offset;
}

void Instruction::branch(uint32_t offset) {
    body.branch.offset = offset;
}

