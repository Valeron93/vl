#include "disassembler.h"
#include "ops.h"

static int print_one_byte_op(FILE* stream, int offset, const char* name)
{
    fprintf(stream, "%s\n", name);
    return offset + 1;
}

static int print_double_op(FILE* stream, Vl_ByteArray bytecode, int offset, const char* name)
{
    // TODO: bounds check
    double value = *(double*)&bytecode.items[offset + 1];
    fprintf(stream, "%s %lf\n", name, value);
    return offset + 1 + sizeof(double);
}

static int print_int_op(FILE* stream, Vl_ByteArray bytecode, int offset, const char* name)
{
    // TODO: bounds check
    int32_t value = *(int32_t*)&bytecode.items[offset + 1];
    fprintf(stream, "%s %d\n", name, value);
    return offset + 1 + sizeof(int32_t);
}

static int disassemble_instruction(FILE* stream, Vl_ByteArray bytecode, int offset)
{
    Vl_Op instruction = (Vl_Op)bytecode.items[offset];
    fprintf(stream, "%06D\t", offset);
    switch (instruction) {
    case VL_OP_NOP:
        return print_one_byte_op(stream, offset, "NOP");

    case VL_OP_PUSH_DOUBLE:
        return print_double_op(stream, bytecode, offset, "PUSH.DOUBLE");

    case VL_OP_ADD:
        return print_one_byte_op(stream, offset, "ADD");

    case VL_OP_JMP:
        return print_int_op(stream, bytecode, offset, "JMP");

    case VL_OP_DUP:
        return print_one_byte_op(stream, offset, "DUP");

    case VL_OP_HALT:
        return print_one_byte_op(stream, offset, "HALT");

    case VL_OP_DBG_PRINT:
        return print_one_byte_op(stream, offset, "PRINT // TODO");
    }
}

void vl_disassemble_bytecode(FILE* stream, Vl_ByteArray bytecode)
{
    int offset = 0;
    while (offset < (int)bytecode.length) {
        offset = disassemble_instruction(stream, bytecode, offset);
    }
}
