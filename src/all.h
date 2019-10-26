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
 *  File name: all.h
 *
 *  Description: Class declarations and constants for all source files. 
 *  See individual description for more details.
 * 
 -----------------------------------------------------------------------*/

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>

using namespace std;

#ifndef ALL_H_
#define ALL_H_

const uint8_t COND_EQ = 0x00;
const uint8_t COND_NE = 0x01;
const uint8_t COND_CS = 0x02;
const uint8_t COND_CC = 0x03;
const uint8_t COND_MI = 0x04;
const uint8_t COND_PL = 0x05;
const uint8_t COND_VS = 0x06;
const uint8_t COND_VC = 0x07;
const uint8_t COND_HI = 0x08;
const uint8_t COND_LS = 0x09;
const uint8_t COND_GE = 0x0A;
const uint8_t COND_LT = 0x0B;
const uint8_t COND_GT = 0x0C;
const uint8_t COND_LE = 0x0D;
const uint8_t COND_AL = 0x0E;

enum PARSER_STATE {
    INITIAL,
    ENTRY,
    AREA,
    PROCEDURE,
    FUNCTION,
    INSTRUCTION,
    COMMENT,
    SUCCESS,
    SYNTAX_ERROR
};

enum MNEMONIC {
    NO_MATCH,
    ADD,
    AND,
    B,
    LDR,
    MOV,
    ORR,
    SUB
};

enum AREA_TYPE {
    CODE,
    DATA
};

enum AREA_PERMISSION {
    READONLY,
    READWRITE
};

class Instruction {
    private:
        MNEMONIC        mnemonic;
        uint32_t        memOffset;
        Instruction*    tlInstructionPtr;

        uint8_t         cond;
        uint8_t         immOperand;

        union {
            // Branch
            struct {
                uint32_t offset;
            } branch;
            // AND, SUB, ADD, MOV
            struct {
                uint8_t rn;
                uint8_t rd;
                union {
                    struct {
                        uint8_t rm;
                        uint8_t shift;
                    } reg;
                    struct {
                        uint8_t rotate;
                        uint8_t imm;
                    } imm;
                } operand2;
            } dataProcessing;
            // LDR, STR
            struct {
                uint8_t rn;
                uint8_t rd;
                uint16_t offset; 
            } singleDataTransfer;
        } body;
        
    public:
        Instruction(MNEMONIC m, uint32_t offset);
        ~Instruction();
        void setTlInstructionPtr(Instruction *tl);
        void setCondition(uint8_t cond);
        void setImmOperand(uint8_t value);
        void setDataProcReg(uint8_t rn, uint8_t rd, uint8_t rm, uint8_t sh);
        void setDataProcImm(uint8_t rn, uint8_t rd, uint8_t ro, uint8_t im);
        void setSingleDataTransfer(uint8_t rn, uint8_t rd, uint16_t offset);
        void setBranch(uint32_t offset);
};

class Function {
    private:
        string          label;
        Instruction*    startInstruction;
        Instruction*    lastInstruction;
        Function*       tlFunctionPtr;
        uint32_t        memOffset;
    
    public:
        Function(string label);
        ~Function();
        Instruction *appendInstruction(Instruction instruction);
        void setTlFunctionPtr(Function *tl);
        void freeInstructions();
};

class Procedure {
    private:
        string          label;
        Procedure*      tlProcedurePtr;

    public:
        Procedure(string label);
        ~Procedure();
        Function *appendFunction(Function function);
        void freeFunctions();
};

class Area {
    private:
        string          name;
        AREA_TYPE       type;
        AREA_PERMISSION permission;
        Procedure*      startProcedurePtr;

    public:
        Area(string _name, AREA_TYPE _type, AREA_PERMISSION _permission);
        Procedure *appendProcedure(Procedure procedure);
        ~Area();
};

MNEMONIC    getMnemonicFromString(string word);
uint8_t     getRegisterFromString(string word);

Instruction*    createInstructionFromLine(string line);

#endif
