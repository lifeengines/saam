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
    { "R0"  , R0  },
    { "R1"  , R1  },
    { "R2"  , R2  },
    { "R3"  , R3  },
    { "R4"  , R4  },
    { "R5"  , R5  },
    { "R6"  , R6  },
    { "R7"  , R7  },
    { "R8"  , R8  },
    { "R9"  , R9  },
    { "R10" , R10 },
    { "R11" , R11 },
    { "R12" , R12 },
    { "R13" , R13 },
    { "R14" , R14 },
    { "R15" , R15 },
};

MNEMONIC getMnemonicFromString(string word) {
    try {
        return mnemonicTable.at(word);
    }
    catch (out_of_range) {
        return NO_MATCH;
    }
}

uint8_t getRegisterFromString(string word) {
    try {
        return registerTable.at(word);
    }
    catch (out_of_range) {
        return 0x00;
    }
}

Instruction *createInstructionFromLine(string line) {
    smatch m;
    if (regex_match(line, m, DATAPROC_REG_OP2_REGEX)) {
        cout << "REG_OP2" << "\n";
    }
    else if (regex_match(line, m, DATAPROC_IMMVAL_OP2_REGEX)){
        cout << "IMVAL_OP2" << "\n";
    }
    else {
        cout << "No match" << "\n";
    }
    return NULL;
}
