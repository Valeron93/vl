#!/usr/bin/env python3

# VM implementation in Python
# Probably will be removed

import argparse
from bytecode import Bytecode
from vlasm import eprint
import struct


def read_bytes(input: str) -> bytes:
    with open(input, "rb") as file:
        return file.read()


def execute(input_filename: str, verbose: bool = False) -> None:
    bc = read_bytes(input_filename)

    stack = []
    pc = 0

    while pc < len(bc):
        instruction = Bytecode(bc[pc])

        match instruction:
            case Bytecode.PUSH_DOUBLE:
                (value,) = struct.unpack("<d", bc[pc + 1 : pc + 9])
                stack.append(value)
                pc += 9

            case Bytecode.ADD:
                value1, value2 = stack.pop(), stack.pop()
                stack.append(value1 + value2)
                pc += 1

            case Bytecode.JMP:
                (offset,) = struct.unpack("<i", bc[pc + 1 : pc + 5])
                pc = offset

            case Bytecode.DBG_PRINT:
                value = stack.pop()
                print("debug print:", value)
                pc += 1

            case Bytecode.DUP:
                value = stack[-1]
                stack.append(value)
                pc += 1

            case Bytecode.HALT:
                print("halt")
                return
            case _:
                eprint("illegal instruction:", repr(instruction))
                exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("filename", help="file to execute")
    parser.add_argument("-v", "--verbose", help="print debug messages")

    args = parser.parse_args()
    eprint("INFO: executing", args.filename)
    execute(args.filename, args.verbose)
