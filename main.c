#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vl/vm/vm.h>

static void usage(const char* program_name)
{
    fprintf(stderr, "Usage: %s <subcommand>\n\n", program_name);
    fprintf(stderr, "Subcommands:\n");
    fprintf(stderr, "    compile <script> [output] - compile script to bytecode\n");
    fprintf(stderr, "    run <script>              - run script\n");
    fprintf(stderr, "    run-bytecode <bytecode>   - run bytecode binary file\n");
    fprintf(stderr, "    help                      - show this message\n");
    fprintf(stderr, "\n");
}

static const char* shift_args(int* argc, char*** argv)
{
    const char* arg = (*argv)[0];

    *argc = *argc - 1;
    *argv = *argv + 1;

    return arg;
}

static bool read_all_file(const char* path, uint8_t** data, size_t* data_size)
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

static void compile_script(const char* script, const char* output_file)
{
    fprintf(stderr, "INFO: compiling '%s', output: '%s'\n", script, output_file);
    assert(0 && "TODO: not implemented");
}

static void run_script(const char* script)
{
    fprintf(stderr, "INFO: running script '%s'\n", script);
    assert(0 && "TODO: not implemented");
}

static void run_bytecode(const char* bytecode_file)
{
    fprintf(stderr, "INFO: running bytecode '%s'\n", bytecode_file);

    uint8_t* bytecode = NULL;
    size_t bytecode_size = 0;

    if (!read_all_file(bytecode_file, &bytecode, &bytecode_size)) {
        fprintf(stderr, "ERROR: failed to read file %s: %s\n", bytecode_file, strerror(errno));
    }

    Vl_Vm vm = { 0 };

    vl_vm_load_bytecode(&vm, bytecode, bytecode_size);
    if (!vl_vm_execute(&vm)) {
        exit(1);
    }

    free(bytecode);
}

int main(int argc, char** argv)
{
    const char* program = shift_args(&argc, &argv);

    if (!argc) {
        usage(program);
        fprintf(stderr, "ERROR: no subcommand provided\n");
        return 1;
    }

    const char* subcommand = shift_args(&argc, &argv);

    if (strcmp(subcommand, "compile") == 0) {

        if (!argc) {
            usage(program);
            fprintf(stderr, "ERROR: no script was provided\n");
            return 1;
        }

        const char* script = shift_args(&argc, &argv);
        const char* output_file = "output.bin";

        if (argc) {
            output_file = shift_args(&argc, &argv);
        }

        compile_script(script, output_file);

    } else if (strcmp(subcommand, "run") == 0) {
        if (!argc) {
            usage(program);
            fprintf(stderr, "ERROR: no script was provided\n");
            return 1;
        }

        const char* script = shift_args(&argc, &argv);
        run_script(script);

    } else if (strcmp(subcommand, "run-bytecode") == 0) {
        if (!argc) {
            usage(program);
            fprintf(stderr, "ERROR: no file was provided\n");
            return 1;
        }
        const char* bytecode_file = shift_args(&argc, &argv);
        run_bytecode(bytecode_file);

    } else if (strcmp(subcommand, "help") == 0) {
        usage(program);
        return 0;

    } else {
        usage(program);
        fprintf(stderr, "ERROR: unknown subcommand: '%s'\n", subcommand);
        return 1;
    }

    return 0;
}
