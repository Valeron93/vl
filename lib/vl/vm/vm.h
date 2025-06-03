#ifndef VM_H_
#define VM_H_

// NOTE: current implementation of virtual machine
// may be frequently changed

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VL_VM_STACK_SIZE 1024

typedef enum Vl_ValueType {
    VL_VALUE_TYPE_NULL,
    VL_VALUE_TYPE_DOUBLE,
} Vl_ValueType;

typedef enum Vl_VmErrorCode {
    VL_VM_SUCCESS = 0,
    VL_VM_FAILURE = 1,
    VL_VM_ILLEGAL_INSTRUCTION = 2,
} Vl_VmErrorCode;

typedef struct Vl_Value {
    Vl_ValueType type;
    union {
        double as_double;
    } value;
} Vl_Value;

typedef struct Vl_Vm {
    uint8_t* bytecode;
    size_t bytecode_size;

    int32_t stack_pointer;
    size_t program_counter;

    Vl_Value stack[VL_VM_STACK_SIZE];
} Vl_Vm;

void vl_vm_load_bytecode(Vl_Vm* vm, uint8_t* bytecode, size_t bytecode_size);

Vl_VmErrorCode vl_vm_execute(Vl_Vm* vm);

#endif // VM_H_
