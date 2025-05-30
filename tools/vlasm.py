#!/usr/bin/env python3

import argparse
import sys
from enum import IntEnum, auto
import struct


from bytecode import Bytecode


def eprint(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)


def assemble_file(input_path, output_path):

    with open(input_path, "r") as input_file:
        lines = [
            line.strip() for line in input_file.readlines() if line.strip()
        ]

        instructions: list[tuple[Bytecode, any]] = []
        pc = 0
        labels = {}
        for line in lines:
            if line.startswith("label"):
                label = line.split()[1].rstrip(":").strip()
                labels[label] = pc
                continue

            match line.split():
                case ["push.d", double_str]:
                    instructions.append(
                        (Bytecode.PUSH_DOUBLE, float(double_str))
                    )
                    pc += 9

                case ["jmp", label]:
                    instructions.append((Bytecode.JMP, label))
                    pc += 5

                case ["add"]:
                    instructions.append((Bytecode.ADD, None))
                    pc += 1

                case ["dbg.print"]:
                    instructions.append((Bytecode.DBG_PRINT, None))
                    pc += 1
                case ["halt"]:
                    instructions.append((Bytecode.HALT, None))
                    pc += 1
                case ["dup"]:
                    instructions.append((Bytecode.DUP, None))
                    pc += 1
                case _:
                    eprint("ERROR: illegal instruction:", line)
                    exit(1)

        with open(output_path, "wb") as output:
            for instruction, arg in instructions:
                output.write(struct.pack("<B", instruction))
                match arg:
                    case float():
                        output.write(struct.pack("<d", arg))
                    case int():
                        output.write(struct.pack("<i", arg))
                    case str():
                        offset = labels[arg]
                        print(label, offset)
                        output.write(struct.pack("<i", offset))

if __name__ == "__main__":
    parser = argparse.ArgumentParser()

    parser.add_argument("filename")
    parser.add_argument(
        "-o", "--output", help="output filename", default="output.bin"
    )

    args = parser.parse_args()

    eprint(f"INFO: compiling '{args.filename}' to '{args.output}'")

    assemble_file(args.filename, args.output)
