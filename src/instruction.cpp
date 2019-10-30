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

Instruction::Instruction(MNEMONIC m, uint32_t offset, uint8_t c) {
    mnemonic    = m;
    memOffset   = offset;
    cond        = c;
};

Instruction::~Instruction(){};

void Instruction::setTlInstructionPtr(Instruction *tl) {
    tlInstructionPtr = tl;
};

DataProc::DataProc(MNEMONIC m, uint32_t offset, uint8_t c) 
        : Instruction(m, offset , c) {};

DataProc::~DataProc() {};

void DataProc::setRegisterRn(REGISTER r) {
    rn = r;
};
void DataProc::setRegisterRd(REGISTER r) {
    rd = r;
};
void DataProc::setImmOperand(uint8_t imm) {
    immOperand = imm;
};

// bool DataProc::setRegOperand2_ImmValShift(uint8_t type, uint8_t amount) {
// };

// bool DataProc::setRegOperand2_RegShift(REGISTER r, uint8_t type) {
//     operand2.regOperand2.shift.regShift.shiftReg = r;
// };

// bool DataProc::setImmOperand2 (uint8_t rotate, uint8_t imm) {

// };

// uint32_t DataProc::get32BitInstruction() {

// };

