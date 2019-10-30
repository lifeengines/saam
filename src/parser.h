#include "all.h"
#include "instruction.h"

Instruction *createInstructionFromLine(string line);
MNEMONIC getMnemonicFromString(string word);
uint8_t getRegisterFromString(string word);