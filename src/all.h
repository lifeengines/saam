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

#define _INSTRUCTION_DEBUG_

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue> 
#include <regex>

#ifndef ALL_H_
#define ALL_H_

enum PARSER_STATE {
    PARSER_INITIAL,
    PARSER_ENTRY,
    PARSER_AREA,
    PARSER_PROCEDURE,
    PARSER_FUNCTION,
    PARSER_INSTRUCTION,
    PARSER_COMMENT,
    PARSER_SUCCESS,
    PARSER_SYNTAX_ERROR
};

enum LINE_TYPE {
    DATAPROC_REG_OP2,
    DATAPROC_IMMVAL_OP2,
    AREA_DIRECTIVE,
    NO_MATCH_LINE
};

/*=============================================================================
 * Regexes
 *===========================================================================*/

const std::string SPACE              = "\\s*";
const std::string OPCODE_REGEX       = "[A-Z]{3}|[a-z]{3}";
const std::string COND_REGEX         = "[A-Z]{0,2}|[a-z]{0,2}";
const std::string UPDATE_FLAG        = "[sS]{0,1}";
const std::string REGISTER_REGEX     = "\\w{2,3}";
const std::string REG_SHIFT_NAME     = "\\w{3}";
const std::string REG_SHIFT_AMOUNT   = "#\\d{1,2}|\\w{2,3}";
const std::string IMM_VAL_DEC        = "#\\d+";
const std::string IMM_VAL_HEX        = "#0x(?:\\d|[A-F]|[a-f])+";
const std::string COMMENT_REGEX      = "(?:;.*)*";

/*=============================================================================
 * Data Processing Instruction 
 * ===========================
 * Register Operand 2 Regex: <opcode>{s}{cond} Rd {, Rn} ,Rm {,<name><amount>}
 *      + Capture group 1: Opcode
 *      + Capture group 2: Update flag
 *      + Capture group 3: Condition flag
 *      + Capture group 4: Register #1
 *      + Capture group 5: <Optional> Register #2 
 *      + Capture group 6: Register #3
 *      + Capture group 7: <Optional> Shift name [ASR, LSL, LSR, ROR] 
 *      + Caputre group 8: <Optional> Shift amount [#n (0<=n<=32) | Register]
 * 
 * ImmVal Operand 2 Regex: <opcode>{s}{cond} Rd {, Rn}, {hex|dec}
 *      + Capture group 1: Opcode
 *      + Capture group 2: Update flag
 *      + Capture group 3: Condition flag
 *      + Capture group 4: Register #1
 *      + Capture group 5: <Optional> Register #2
 *      + Capture group 6: Hex/Dec immediate value
 *===========================================================================*/

const std::regex DATAPROC_REG_OP2_REGEX(
    "("     + OPCODE_REGEX      + ")"   +
    "("     + UPDATE_FLAG       + ")"   +
    "("     + COND_REGEX        + ")"   + SPACE +
    "("     + REGISTER_REGEX    + ")"   + SPACE +
    "(?:,"  + SPACE             + "("   + REGISTER_REGEX    
            + ")){0,1}"         + SPACE +
    "(?:,"  + SPACE             + "("   + REGISTER_REGEX    + ")"   
            + SPACE             + "(?:("+ REG_SHIFT_NAME    + ")"
            + SPACE             + "("   + REG_SHIFT_AMOUNT  + ")){0,1})"
            + SPACE             + COMMENT_REGEX);

const std::regex DATAPROC_IMMVAL_OP2_REGEX(
    "("     + OPCODE_REGEX      + ")"   +
    "("     + UPDATE_FLAG       + ")"   +
    "("     + COND_REGEX        + ")"   + SPACE +
    "("     + REGISTER_REGEX    + ")"   + SPACE +
    "(?:,"  + SPACE             + "("   + REGISTER_REGEX    
            + ")){0,1}"         + SPACE 
            + ","               + SPACE +
    "("     + IMM_VAL_HEX       + "|"   + IMM_VAL_DEC + ")"
            + SPACE             + COMMENT_REGEX);

/*=============================================================================
 * Branch Exchange Instruction (BX)
 * ================================
 * Branch Exchange Instruction Regex: <BX|bx>{cond} Rn
 *      + Capture group 1: opcode
 *      + Capture group 2: cond
 *      + Capture group 3: Exchange register
 * 
 * Branch Instruction (B, BL)
 * ==========================
 * Branch Instruction RegexL <B|b>{L} {cond} <label>
 *      + Capture group 1: opcode
 *      + Capture group 2: L
 *      + Capture group 3: cond
 *      + Capture group 4: label
 * 
 *===========================================================================*/

const std::string BRANCH_EXCHANGE_OPCODE_REGEX = "BX|bx";
const std::string BRANCH_OPCODE_REGEX = "B|b";
const std::string BRANCH_LR_REGEX = "L|l";
const std::string BRANCH_LABEL = "\\w+";

const std::regex BRANCH_EXCHANGE_REGEX(
    "(" + BRANCH_EXCHANGE_OPCODE_REGEX  + ")" + SPACE +
    "(" + COND_REGEX                    + ")" + SPACE +
    "(" + REGISTER_REGEX                + ")" + SPACE + COMMENT_REGEX);

const std::regex BRANCH_REGEX(
    "(" + BRANCH_OPCODE_REGEX           + ")" + 
    "(" + BRANCH_LR_REGEX               + ")" + SPACE +
    "(" + COND_REGEX                    + ")" + SPACE +
    "(" + BRANCH_LABEL                  + ")" + SPACE + COMMENT_REGEX);

enum ERROR_TYPE {
    INVALID_TOKEN,
    INVALID_VALUE,
    OUT_OF_RANGE_VALUE,
    INVALID_SYNTAX,
    ILL_FORMAT_INSTRUCTION,
    UNLINKED_LABEL,
    UNLINKED_AREA
};

enum MNEMONIC {
    NO_MATCH_MNEMONIC,
    // Data Processing Instructions
    AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, 
    TEQ, CMP, CMN, ORR, MOV, BIC, MVN,
    
    // Branch Instructions
    BX, B  
};

enum OPERAND2_SHIFT {
    NO_MATCH_SHIFT,
    NO_SHIFT,
    ASR,
    LSL,
    LSR,
    ROR
};

enum UPDATE_REGS {
    NO_MATCH_UPDATE_REG,
    UPDATE_TRUE,
    UPDATE_FALSE
};

enum CONDITION {
    NO_MATCH_COND,
    NO_COND,
    EQ,
    NE,
    CS,
    CC,
    MI,
    PL,
    VS,
    VC,
    HI,
    LS,
    GE,
    LT,
    GT,
    LE,
    AL
};

enum REGISTER {
    NO_MATCH_REGISTER,
    NO_REG,
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
