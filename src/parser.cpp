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
 *  File name: parser.cpp
 *
 *  Description:
 * 
 -----------------------------------------------------------------------*/

#include "parser.h"

const std::unordered_map<std::string, MNEMONIC> mnemonicTable = {
    // Data Processing Instructions
    {"AND", AND}, {"EOR", EOR}, {"SUB", SUB}, {"RSB", RSB}, {"ADD", ADD},
    {"ADC", ADC}, {"SBC", SBC}, {"RSC", RSC}, {"TST", TST}, {"TEQ", TEQ},
    {"CMP", CMP}, {"CMN", CMN}, {"ORR", ORR}, {"MOV", MOV}, {"BIC", BIC},
    {"MVN", MVN}
};

const std::unordered_map<std::string, REGISTER> registerTable = {
    { "R0"  , R0  }, { "r0"  , R0  },
    { "R1"  , R1  }, { "r1"  , R1  },
    { "R2"  , R2  }, { "r2"  , R2  },
    { "R3"  , R3  }, { "r3"  , R3  },
    { "R4"  , R4  }, { "r4"  , R4  },
    { "R5"  , R5  }, { "r5"  , R5  },
    { "R6"  , R6  }, { "r6"  , R6  },
    { "R7"  , R7  }, { "r7"  , R7  },
    { "R8"  , R8  }, { "r8"  , R8  },
    { "R9"  , R9  }, { "r9"  , R9  },
    { "R10" , R10 }, { "r10" , R10 },
    { "R11" , R11 }, { "r11" , R11 },
    { "R12" , R12 }, { "r12" , R12 }, { "IP", R12 }, { "ip", R12 },
    { "R13" , R13 }, { "r13" , R13 }, { "SP", R13 }, { "sp", R13 },
    { "R14" , R14 }, { "r14" , R14 }, { "LR", R14 }, { "lr", R14 },
    { "R15" , R15 }, { "r15" , R15 }, { "PC", R15 }, { "pc", R15 },
    { ""    , NO_REG }
};

const std::unordered_map<std::string, CONDITION> condTable = {
    {"EQ", EQ}, {"eq", EQ},
    {"NE", NE}, {"ne", NE},
    {"CS", CS}, {"cs", CS},
    {"CC", CC}, {"cc", CC},
    {"MI", MI}, {"mi", MI},
    {"PL", PL}, {"pl", PL},
    {"VS", VS}, {"vs", VS},
    {"VC", VC}, {"vc", VC},
    {"HI", HI}, {"hi", HI},
    {"LS", LS}, {"ls", LS},
    {"GE", GE}, {"ge", GE},
    {"LT", LT}, {"lt", LT},
    {"GT", GT}, {"gt", GT},
    {"LE", LE}, {"le", LE},
    {"AL", AL}, {"al", AL},
    {""  , NO_COND}
};

const std::unordered_map<std::string, OPERAND2_SHIFT> shiftTable = {
    {"ASR", ASR}, {"LSL", LSL}, {"LSR", LSR}, {"ROR", ROR},
    {"asr", ASR}, {"lsl", LSL}, {"lsr", LSR}, {"ror", ROR},
    {"", NO_SHIFT}
};

namespace {
    MNEMONIC getMnemonicFromString(std::string word, uint32_t lineNum, 
                                        ErrorQueue &q) {
        try {
            return mnemonicTable.at(word);
        }
        catch (std::out_of_range) {
            Error e = { lineNum, INVALID_TOKEN, word };
            q.addError(e);
            return NO_MATCH_MNEMONIC;
        }
    }

    UPDATE_REGS getUpdateFlagFromString(std::string word, uint32_t lineNum,
                                        ErrorQueue &q) {
        if (word != "s" && word != "S" && word != "") {
            Error e = { lineNum, INVALID_TOKEN, word };
            q.addError(e);
            return NO_MATCH_UPDATE_REG;
        }
        return (word == "s" || word == "S") ? UPDATE_TRUE : UPDATE_FALSE;
    }

    REGISTER getRegisterFromString(std::string word, uint32_t lineNum, 
                                        ErrorQueue &q) {
        try {
            return registerTable.at(word);
        }
        catch (std::out_of_range) {
            Error e = { lineNum, INVALID_TOKEN, word };
            q.addError(e);
            return NO_MATCH_REGISTER;
        }
    }

    CONDITION getCondFromString(std::string word, uint32_t lineNum, 
                                        ErrorQueue &q) {
        try {
            return condTable.at(word);
        }
        catch (std::out_of_range) {
            Error e = { lineNum, INVALID_TOKEN, word };
            q.addError(e);
            return NO_MATCH_COND;
        }
    }

    OPERAND2_SHIFT getShiftFromString(std::string word, uint32_t lineNum, 
                                        ErrorQueue &q) {
        try {
            return shiftTable.at(word);
        }
        catch (std::out_of_range) {
            Error e = { lineNum, INVALID_TOKEN, word };
            q.addError(e);
            return NO_MATCH_SHIFT;
        }
    }
}

LINE_TYPE getLineType(std::string &line, std::smatch &match) {
    std::smatch m;
    if (std::regex_match(line, m, DATAPROC_REG_OP2_REGEX)) {
        match = m;
        return DATAPROC_REG_OP2;
    }

    else if (std::regex_match(line, m, DATAPROC_IMMVAL_OP2_REGEX)) {
        match = m;
        return DATAPROC_IMMVAL_OP2;
    }

    else {
        return NO_MATCH_LINE;
    }
}

Instruction *createDataProcRegOp2(std::smatch sm, uint32_t mem, 
                                    uint32_t lineNum, ErrorQueue &q) {

    std::string mnemonic    = sm.str(1);
    std::string updateFlag  = sm.str(2);
    std::string cond        = sm.str(3);
    std::string reg_1       = sm.str(4);
    std::string reg_2       = sm.str(5);
    std::string reg_3       = sm.str(6);
    std::string shiftName   = sm.str(7);
    std::string shiftAmt    = sm.str(8);

    MNEMONIC m = getMnemonicFromString(mnemonic, lineNum, q);
    if (m == NO_MATCH_MNEMONIC) return nullptr;

    UPDATE_REGS u = getUpdateFlagFromString(updateFlag, lineNum, q);
    if (u == NO_MATCH_UPDATE_REG) return nullptr;

    CONDITION c = getCondFromString(cond, lineNum, q);
    if (c == NO_MATCH_COND) return nullptr;

    REGISTER rn = getRegisterFromString(reg_1, lineNum, q);
    if (rn == NO_MATCH_REGISTER) return nullptr;

    REGISTER rd = getRegisterFromString(reg_2, lineNum, q);
    if (rd == NO_MATCH_REGISTER) return nullptr;

    REGISTER rm = getRegisterFromString(reg_3, lineNum, q);
    if (rn == NO_MATCH_REGISTER) return nullptr;

    OPERAND2_SHIFT s = getShiftFromString(shiftName, lineNum, q);
    
    uint8_t sAmount = 0;
    REGISTER sReg = NO_REG;

    switch (s) {
        case NO_MATCH_SHIFT:
            return nullptr;
        case NO_SHIFT:
            if (shiftAmt != "") {
                Error e = { lineNum, INVALID_SYNTAX, shiftAmt };
                q.addError(e);
                return nullptr;
            }
            break;
        default:
            if (shiftAmt == "") {
                Error e = { lineNum, INVALID_SYNTAX, shiftAmt };
                q.addError(e);
                return nullptr;
            }
            // shift immval n from 1 to 31
            else if (shiftAmt[0] == '#') {
                uint8_t sAmtStringToInt = stoi(shiftAmt.substr(1));
                if ((sAmtStringToInt < 0) || (sAmtStringToInt > 32)) {
                    Error e = { lineNum, OUT_OF_RANGE_VALUE, shiftAmt };
                    q.addError(e);
                    return nullptr;
                }
                else {
                    sAmount = sAmtStringToInt;
                }
            }
            // shift register
            else {
                sReg = getRegisterFromString(shiftAmt.substr(1), lineNum, q);
                if (sReg == NO_MATCH_REGISTER) return nullptr;
            } 
            break;
    }

    // Return instruction
    regOperand2 op2;
    if (sAmount == 0) {
        op2.regOperand2Type = 0x01;
        op2.rm = rm;
        op2.shift.regShift.type = s;
        op2.shift.regShift.shiftReg = sReg;
    }
    else {
        op2.regOperand2Type = 0x00;
        op2.rm = rm;
        op2.shift.immValShift.type = s;
        op2.shift.immValShift.shiftAmount = sAmount;
    }
    
    return new DataProc(mem, m, u, c, rn, rd, op2);
}

// Instruction *createDataProcImmValOp2(std::smatch sm, uint32_t mem, 
//                                     uint32_t lineNum, ErrorQueue &q) {

// }