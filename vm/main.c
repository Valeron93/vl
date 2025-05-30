#include "vm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void usage(char* program)
{
    fprintf(stderr, "Usage: %s <filename>\n", program);
}

bool read_all_file(const char* path, uint8_t** data, size_t* data_size)
{
    FILE* file = fopen(path, "rb");

    if (file == NULL) {
        return false;
    }

    fseek(file, 0, SEEK_END);
    *data_size = ftell(file);
    *data = (uint8_t*)malloc(*data_size);
    fseek(file, 0, SEEK_SET);

    fread(*data, *data_size, 1, file);
    fclose(file);

    return true;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    fprintf(stderr, "Executing %s\n", filename);

    uint8_t* bytecode = NULL;
    size_t bytecode_size = 0;
    if (!read_all_file(filename, &bytecode, &bytecode_size)) {
        fprintf(stderr, "ERROR: // TODO: failed to read file\n");
        return EXIT_FAILURE;
    }
    Vl_Vm vm = { 0 };

    vl_vm_load_bytecode(&vm, bytecode, bytecode_size);
    vl_vm_execute(&vm);

    free(bytecode);
}