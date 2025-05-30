#ifndef OPS_H_
#define OPS_H_

typedef enum Vl_Op {
    VL_OP_NOP = 0,
    VL_OP_PUSH_DOUBLE = 1,
    VL_OP_ADD = 2,
    VL_OP_JMP = 4,
    VL_OP_DUP = 5,
    VL_OP_HALT = 255,

    // this instructions are to be removed
    VL_OP_DBG_PRINT = 254,
} Vl_Op;

#endif // OPS_H_