#include "all.h"
#include "instruction.h"
#include "bitops.h"
#include "error.h"

#ifndef PARSER_H_
#define PARSER_H_

LINE_TYPE getLineType(std::string &line, std::smatch &match);

Instruction *createDataProcRegOp2(std::smatch sm, uint32_t mem, 
                                    uint32_t lineNum, ErrorQueue &q);

Instruction *createDataProcImmValOp2(std::smatch sm, uint32_t mem, 
                                    uint32_t lineNum, ErrorQueue &q);

#endif