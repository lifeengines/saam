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
 *  File name: instruction.h
 *
 *  Description: Instruction class and subclasses declarations and constants.
 *  See individual description for more details.
 * 
 -----------------------------------------------------------------------*/

#include "all.h"

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

class Instruction {
    protected:
        MNEMONIC    mnemonic;
        uint32_t    memOffset;
        UPDATE_REGS updateFlag;
        CONDITION   cond;

    public:
        Instruction( uint32_t offset, MNEMONIC m, UPDATE_REGS u, CONDITION c);
        virtual ~Instruction();
        uint32_t getMemOffset();
        void setMemOffset(uint32_t offset);

    /* INSTRUCTION DEBUG */
    #ifdef _INSTRUCTION_DEBUG_
    public:
        virtual std::string printInstructionString();
    #endif
};

struct regOperand2 {
    REGISTER rm;
    /* 0x00 - immValShift, 0x01 - regShift */
    uint8_t regOperand2Type;

    union {
        struct {
            OPERAND2_SHIFT type;
            uint8_t shiftAmount;
        } immValShift;
        struct {
            OPERAND2_SHIFT type;
            REGISTER shiftReg;
        } regShift;
    } shift;
};

struct immOperand2 {
    uint8_t rotate;
    uint8_t imm;
};

class DataProc : public Instruction {
    private:
        REGISTER rn;
        REGISTER rd;

    /* 0x00 - regOp, 0x01 - immOp */
    private:
        uint8_t immOperand;

    private:
        union {
            regOperand2 regOp;
            immOperand2 immOp;
        } operand2;

    public:
        DataProc(uint32_t offset, MNEMONIC m, UPDATE_REGS u, CONDITION c,
        REGISTER _rn, REGISTER _rd, regOperand2 &_regOp);
        DataProc(uint32_t offset, MNEMONIC m, UPDATE_REGS u, CONDITION c,
        REGISTER _rn, REGISTER _rd, immOperand2 &_immOp);
        ~DataProc();

    public:
        uint32_t get32BitInstruction();

    /* INSTRUCTION DEBUG */
    #ifdef _INSTRUCTION_DEBUG_
    public:
        std::string printInstructionString();
    #endif
};

#endif