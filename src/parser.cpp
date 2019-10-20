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

#include "all.h"

unordered_map<string, MNEMONIC> mnemonicTable = {
    {"ADD"  , ADD},
    {"AND"  , AND},
    {"B"    , B},
    {"LDR"  , LDR},
    {"MOV"  , MOV},
    {"ORR"  , ORR},
    {"SUB"  , SUB}
};

unordered_map<string, uint8_t> registerTable = {
    {"r0"   , 0x01},
    {"r1"   , 0x02},
    {"r2"   , 0x03},
    {"r3"   , 0x04},
    {"r4"   , 0x05},
    {"r5"   , 0x06},
    {"r6"   , 0x07},
    {"r7"   , 0x08},
    {"r8"   , 0x09},
    {"r9"   , 0x0A},
    {"r10"  , 0x0B},
    {"r11"  , 0x0C},
    {"r12"  , 0x0D},
};

MNEMONIC getMnemonicFromString(string word) {
    try {
        return mnemonicTable.at(word);
    }
    catch (out_of_range) {
        return NO_MATCH;
    }
}