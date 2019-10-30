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
 *  Description: Instruction class declarations and constants. 
 *  See individual description for more details.
 * 
 -----------------------------------------------------------------------*/

#include "all.h"

using namespace std;

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

class Instruction {
    protected:
        MNEMONIC        mnemonic;
        uint32_t        memOffset;
        Instruction*    tlInstructionPtr;
        CONDITION       cond;

    public:
        Instruction(MNEMONIC m, uint32_t offset, CONDITION c);
        ~Instruction();
        void setTlInstructionPtr(Instruction *tl);
};

class DataProc : public Instruction {
    private:
        REGISTER rn;
        REGISTER rd;
        uint8_t immOperand;

        union {
            struct {
                REGISTER rm;
                union {
                    struct {
                        uint8_t shiftType;
                        uint8_t shiftAmount;
                    } immValShift;
                    struct {
                        uint8_t shiftType;
                        REGISTER shiftReg;
                    } regShift;
                } shift;
            } regOperand2;
            struct {
                uint8_t rotate;
                uint8_t imm;
            } immOperand2;
        } operand2;

    public:
        DataProc(MNEMONIC m, uint32_t offset, CONDITION c);
        ~DataProc();
        void setRegisterRn(REGISTER r);
        void setRegisterRd(REGISTER r);
        void setImmOperand(uint8_t imm);
       
        bool setRegOperand2_ImmValShift (uint8_t type, uint8_t amount);
        bool setRegOperand2_RegShift    (REGISTER r, uint8_t type);
        bool setImmOperand2 (uint8_t rotate, uint8_t imm);

        uint32_t get32BitInstruction();
};

#endif