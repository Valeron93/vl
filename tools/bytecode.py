from enum import IntEnum

class Bytecode(IntEnum):
    PUSH_DOUBLE = 1
    ADD = 2
    JMP = 4
    DUP = 5
    
    HALT = 255

    DBG_PRINT = 254