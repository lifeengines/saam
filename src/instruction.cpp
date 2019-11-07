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

/*=============================================================================
 * Instruction debug lookup tables
 *===========================================================================*/
#ifdef _INSTRUCTION_DEBUG_

std::string mnemonicReverseTable[] = {
    "NO_MATCH_MNEMONIC",
    "ADD",
    "AND",
    "B",
    "LDR",
    "MOV",
    "ORR",
    "SUB"
};

std::string operand2ShiftReverseTable[] = {
    "NO_MATCH_SHIFT", "", "ASR", "LSL", "LSR", "ROR"
};

std::string conditionReverseTable[] = {
    "NO_MATCH_COND", "", "EQ", "NE", "CS", "CC", "MI", 
    "PL", "VS", "VC","HI", "LS", "GE", "LT", "GT", "LE", "AL"
};

std::string registerReverseTable[] = {
    "NO_MATCH_REGISTER", "", "R0", "R1", "R2", "R3", "R4", "R5",
    "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"
}; 

#endif

/*=============================================================================
 * Instruction base class
 *===========================================================================*/
Instruction::Instruction(uint32_t offset, MNEMONIC m, bool s, CONDITION c) {
    mnemonic    = m;
    memOffset   = offset;
    cond        = c;
    updateFlag  = s;
};

Instruction::~Instruction() {};

uint32_t Instruction::getMemOffset() {
    return memOffset;
};

void Instruction::setMemOffset(uint32_t offset) {
    memOffset = offset;
};

/*=============================================================================
 * Data Processing Instruction subclass
 * Syntax: <opcode>{s}{cond} Rd, Rn {,Rm} {,<name><amount>}
 *===========================================================================*/
DataProc::DataProc  (uint32_t offset, MNEMONIC m, bool s, CONDITION c,
                    REGISTER _rn, REGISTER _rd, regOperand2 &_regOp)
                    : Instruction(offset, m, s, c) { 
    operand2.regOp = _regOp;
    rn             = _rn;
    rd             = _rd;
    immOperand     = 0;                      
};

DataProc::DataProc  (uint32_t offset, MNEMONIC m, bool s, CONDITION c,
                    REGISTER _rn, REGISTER _rd, immOperand2 &_immOp)
                    : Instruction(offset, m, s, c) {                       
    operand2.immOp = _immOp;
    rn             = _rn;
    rd             = _rd;
    immOperand     = 1;   
};

DataProc::~DataProc() {};

#ifdef _INSTRUCTION_DEBUG_
std::string DataProc::getInstructionString() {
    // std::cout << "HELLO FROM INSTRUCTION" << std::endl;
    return 
        mnemonicReverseTable[mnemonic]
        + (updateFlag ? "s" : "")
        + conditionReverseTable[cond]
        + registerReverseTable[rn]
        + registerReverseTable[rd];
};
#endif /* INSTRUCTION DEBUG */