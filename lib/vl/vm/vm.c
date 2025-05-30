#include "vm.h"

#include "ops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static Vl_Value vm_stack_pop(Vl_Vm* vm)
{
    // TODO: check if stack is empty
    Vl_Value value = vm->stack[vm->stack_pointer];
    vm->stack_pointer--;
    return value;
}

static Vl_Value vm_stack_peek(Vl_Vm* vm)
{
    // TODO: check if stack is empty
    return vm->stack[vm->stack_pointer];
}

static void vm_stack_push(Vl_Vm* vm, Vl_Value value)
{
    // TODO: check for stack overflow
    if (vm->stack_pointer >= VL_VM_STACK_SIZE - 2) {
        exit(1);
    }
    vm->stack_pointer++;
    vm->stack[vm->stack_pointer] = value;
}

void vl_vm_load_bytecode(Vl_Vm* vm, uint8_t* bytecode, size_t bytecode_size)
{
    vm->bytecode = bytecode;
    vm->bytecode_size = bytecode_size;
    vm->program_counter = 0;
    vm->stack_pointer = -1;
}

Vl_VmErrorCode vl_vm_execute(Vl_Vm* vm)
{

    while (vm->program_counter < vm->bytecode_size) {
        uint8_t instruction = vm->bytecode[vm->program_counter];

        switch (instruction) {

        case VL_OP_NOP: {
            vm->program_counter += 1;
        } break;

        case VL_OP_PUSH_DOUBLE: {
            // TODO: handle cases when there instruction
            //  is malformed and there is no double
            double value = *(double*)(vm->bytecode + vm->program_counter + 1);
            vm_stack_push(vm, (Vl_Value) {
                                  .type = VL_VALUE_TYPE_DOUBLE,
                                  .value.as_double = value,
                              });
            vm->program_counter += 9;
        } break;

        case VL_OP_ADD: {
            Vl_Value value1 = vm_stack_pop(vm);
            assert(value1.type == VL_VALUE_TYPE_DOUBLE);
            Vl_Value value2 = vm_stack_pop(vm);
            assert(value2.type == VL_VALUE_TYPE_DOUBLE);

            Vl_Value sum = {
                .type = VL_VALUE_TYPE_DOUBLE,
                .value.as_double = value1.value.as_double + value2.value.as_double,
            };
            vm_stack_push(vm, sum);
            vm->program_counter += 1;
        } break;

        case VL_OP_JMP: {
            uint32_t offset = *(uint32_t*)(vm->bytecode + vm->program_counter + 1);
            vm->program_counter = offset;
        } break;

        case VL_OP_DBG_PRINT: {
            Vl_Value value = vm_stack_pop(vm);
            printf("debug print: %lf\n", value.value.as_double);
            vm->program_counter += 1;
        } break;

        case VL_OP_DUP: {
            vm_stack_push(vm, vm_stack_peek(vm));
            vm->program_counter += 1;
        } break;

        case VL_OP_HALT: {
            return VL_VM_SUCCESS;
        } break;

        default: {
            fprintf(stderr, "illegal instruction: 0x%X\n", instruction);
            return VL_VM_ILLEGAL_INSTRUCTION;
        } break;
        }
    }
    return VL_VM_SUCCESS;
}
