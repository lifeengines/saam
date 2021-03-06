#------------------------------------------------------------------------
#
#  Small ARM Assembler Module
#  
#  Copyright (c) 2019 - Trung Truong
#  All rights reserved.

#  Permission is hereby granted, free of charge, to any person 
#  obtaining a copy of this software and associated documentation 
#  files (the "Software"), to deal in the Software without restriction,
#  including without limitation the rights to use, copy, modify, merge,
#  publish, distribute, sublicense, and/or sell copies of the Software,
#  and to permit persons to whom the Software is furnished to do so, 
#  subject to the following conditions:
#  
#  The above copyright notice and this permission notice shall be included 
#  in all copies or substantial portions of the Software.
#  
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
#  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
#  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
#  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
#  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
#  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# 
#  File name: Makefile
#
#  Description: Create executables
#------------------------------------------------------------------------

HEADERS  = src/all.h

OBJECTS  = $(SOURCES:.c=.o)
RESULT   = saam

#  Compiler Flags
CC 			= clang++
CFLAGS      = -g -std=c++11 -pedantic -Wall -Werror -Wextra \
              -Wno-overlength-strings -Wfatal-errors -pedantic
LDFLAGS     = -g
CPPFLAGS    = -I.
RM          = rm -f 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm -rf src/*.o tests/*.o core* *~ saam tests/test-*

saam: src/main.o
	$(CC) $(CFLAGS) -o saam src/main.o

# Unit tests
test-instructions: tests/test_instructions.o src/instruction.o \
					src/parser.o src/error.o src/bitops.o
	$(CC) $(CFLAGS) -o tests/test-instructions tests/test_instructions.o \
					src/instruction.o src/parser.o src/error.o src/bitops.o

test-error: tests/test_error.o src/error.o
	$(CC) $(CFLAGS) -o tests/test-error tests/test_error.o src/error.o
