#include "all.h"
#include "instruction.h"
#include "error.h"

#ifndef PARSER_H_
#define PARSER_H_

std::pair<LINE_TYPE, std::smatch> getLineType(std::string line);

DataProc *createDataProcRegOp2(std::smatch sm, uint32_t mem, 
                                    uint32_t lineNum, ErrorQueue &q);

// MNEMONIC getMnemonicFromString(std::string word, uint32_t lineNum,
//                                     ErrorQueue &q);
// REGISTER getRegisterFromString(std::string word, uint32_t lineNum,
//                                     ErrorQueue &q);
// CONDITION getCondFromString(std::string word, uint32_t lineNum,
//                                     ErrorQueue &q);
// OPERAND2_SHIFTNAME getShiftNameFromString(std::string word, uint32_t lineNum,
//                                     ErrorQueue &q);

// Instruction *createInstr(std::string line,  uint32_t lineNum, 
//                                             uint32_t offset, ErrorQueue &q);


#endif