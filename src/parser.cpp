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

using namespace std;

const unordered_map<string, MNEMONIC> mnemonicTable = {
    {"ADD"  , ADD},
    {"AND"  , AND},
    {"B"    , B},
    {"LDR"  , LDR},
    {"MOV"  , MOV},
    {"ORR"  , ORR},
    {"SUB"  , SUB}
};

const unordered_map<string, REGISTER> registerTable = {
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
    { "R15" , R15 }, { "r15" , R15 }, { "PC", R15 }, { "pc", R15 }
};

const unordered_map<string, CONDITION> condTable = {
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
    {"AL", AL}, {"al", AL}
};

MNEMONIC getMnemonicFromString(string word) {
    try {
        return mnemonicTable.at(word);
    }
    catch (out_of_range) {
        return NO_MATCH_MNEMONIC;
    }
}

REGISTER getRegisterFromString(string word) {
    try {
        return registerTable.at(word);
    }
    catch (out_of_range) {
        return NO_MATCH_REGISTER;
    }
}

CONDITION getCondFromString(string word) {
    try {
        return condTable.at(word);
    }
    catch (out_of_range) {
        return NO_MATCH_COND;
    }
}
/*=============================================================================
 * Data Processing Instruction 
 * ===========================
 * Register Operand 2 Regex: <opcode>{s}{cond} Rd, Rn {,Rm} {,<name><amount>}
 *      + Capture group 1: Opcode
 *      + Capture group 2: Update flag
 *      + Capture group 3: Condition flag
 *      + Capture group 4: Register #1
 *      + Capture group 5: Register #2
 *      + Capture group 6: <Optional> Register #3
 *      + Capture group 7: <Optional> Shift name [ASR, LSL, LSR, ROR] 
 *      + Caputre group 8: <Optional> Shift amount [#n (0<=n<=32) | Register]
 */
// Instruction *createDataProcRegOperand2(MNEMONIC m, smatch sm) {

// }

Instruction *createInstructionFromLine(string line) {
    smatch m;
    if (regex_match(line, m, DATAPROC_REG_OP2_REGEX)) {
        switch (getMnemonicFromString(string(m[1]))) {
            case ADD:
                cout << "ADD" << endl;
                break;
            case AND:
                cout << "ADD" << endl;
                break;
            default:
                cout << "NO_MATCH" << endl;
                break;
        }
    }
    else if (regex_match(line, m, DATAPROC_IMMVAL_OP2_REGEX)) {
        cout << "IMVAL_OP2" << "\n";
    }
    else {
        cout << "No match" << "\n";
    }
    return NULL;
}
