#include "all.h"
#include "instruction.h"

#ifndef PARSER_H_
#define PARSER_H_

Instruction *createInstructionFromLine(string line);
MNEMONIC getMnemonicFromString(string word);
REGISTER getRegisterFromString(string word);
CONDITION getCondFromString(string word);

#endif