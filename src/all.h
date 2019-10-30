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
 *  Description: Helper function declarations and constants for 
 *  all source files. See individual description for more details.
 * 
 -----------------------------------------------------------------------*/

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector> 
#include <regex>

using namespace std;

#ifndef ALL_H_
#define ALL_H_

const uint8_t COND_EQ = 0x01;
const uint8_t COND_NE = 0x02;
const uint8_t COND_CS = 0x03;
const uint8_t COND_CC = 0x04;
const uint8_t COND_MI = 0x05;
const uint8_t COND_PL = 0x06;
const uint8_t COND_VS = 0x07;
const uint8_t COND_VC = 0x08;
const uint8_t COND_HI = 0x09;
const uint8_t COND_LS = 0x0A;
const uint8_t COND_GE = 0x0B;
const uint8_t COND_LT = 0x0C;
const uint8_t COND_GT = 0x0D;
const uint8_t COND_LE = 0x0E;
const uint8_t COND_AL = 0x0F;

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

// Regexes
// const regex AREA_REGEX("AREA\\s*(\\w+),\\s*(\\w+),\\s*(\\w+)\\s*(;.*)*");
// const regex PROC_REGEX("(\\w+)\\s*PROC\\s*(;.*)*");

const string SPACE              = "\\s*";
const string OPCODE_REGEX       = "[A-Z]{3}|[a-z]{3}";
const string COND_REGEX         = "[A-Z]{0,2}|[a-z]{0,2}";
const string UPDATE_FLAG        = "[sS]{0,1}";
const string REGISTER_REGEX     = "\\w{2,3}";
const string REG_SHIFT_NAME     = "\\w{3}";
const string REG_SHIFT_AMOUNT   = "#\\d{1,2}|\\w{2,3}";
const string IMM_VAL_DEC        = "#\\d+";
const string IMM_VAL_HEX        = "#0x\\d+";
const string COMMENT_REGEX      = "(?:;.*)*";

/*=============================================================================
 * Data Processing Instruction 
 * ===========================
 * Register Operand 2 Regex: <opcode>{cond}{S} {Rd,} Rn, <Op2>
 *      + Capture group 1: 
 *      + Capture group 2:
 *      + Capture group 3:
 *      + Capture group 4: 
 *      + Capture group 5:
 *      + Capture group 6:
 *===========================================================================*/

const regex DATAPROC_REG_OP2_REGEX(
    "("     + OPCODE_REGEX      + ")"   +
    "("     + UPDATE_FLAG       + ")"   +
    "("     + COND_REGEX        + ")"   + SPACE +
    "("     + REGISTER_REGEX    + ")"   + SPACE + "," + SPACE +
    "("     + REGISTER_REGEX    + ")"   + SPACE +
    "(?:,"  + SPACE             + "("   + REGISTER_REGEX      
            + ")){0,1}"         + SPACE +
    "(?:,"  + SPACE             + "("           + REG_SHIFT_NAME   + ")"
            + SPACE             + "("           + REG_SHIFT_AMOUNT + ")){0,1}"
            + SPACE             + COMMENT_REGEX);

const regex DATAPROC_IMMVAL_OP2_REGEX(
    "("     + OPCODE_REGEX      + ")"   +
    "("     + UPDATE_FLAG       + ")"   +
    "("     + COND_REGEX        + ")"   + SPACE +
    "("     + REGISTER_REGEX    + ")"   + SPACE + "," + SPACE +
    "("     + REGISTER_REGEX    + ")"   + SPACE + "," + SPACE +
    "("     + IMM_VAL_HEX      + "|"   + IMM_VAL_DEC + ")"
            + SPACE             + COMMENT_REGEX);

/*=============================================================================
 * Branch Instruction 
 * ==================
 * Register Operand 2 Regex: <opcode>{cond}{S} {Rd,} Rn, <Op2>
 *      + Capture group 1: 
 *      + Capture group 2:
 *      + Capture group 3:
 *      + Capture group 4: 
 *      + Capture group 5:
 *      + Capture group 6:
 *===========================================================================*/

const regex branchInstruction
("");

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

enum REGISTER {
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,    // IP
    R13,    // SP
    R14,    // LR
    R15,    // PC
};

#endif
