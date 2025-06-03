#ifndef DISSASSEMBLER_H_
#define DISSASSEMBLER_H_

#include <stdio.h>
#include <vl/common/vl_list.h>

void vl_disassemble_bytecode(FILE* stream, Vl_ByteArray bytecode);

#endif // DISSASSEMBLER_H_
