#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vl/common/vl_list.h>
#include <vl/vm/disassembler.h>
#include <vl/vm/vm.h>

static void usage(const char* program_name)
{
    fprintf(stderr, "Usage: %s <subcommand>\n\n", program_name);
    fprintf(stderr, "Subcommands:\n");
    fprintf(stderr, "    compile <script> [output] - compile script to bytecode\n");
    fprintf(stderr, "    run <script>              - run script\n");
    fprintf(stderr, "    run-bytecode <bytecode>   - run bytecode binary file\n");
    fprintf(stderr, "    disasm <bytecode>         - disassemble bytecode binary file\n");
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

static Vl_ByteArray read_all_file(const char* path)
{
    FILE* file = fopen(path, "rb");

    Vl_ByteArray result = { 0 };
    if (file == NULL) {
        return (Vl_ByteArray) { 0 };
    }

    fseek(file, 0, SEEK_END);
    result.length = ftell(file);
    result.capacity = result.length;
    result.items = (uint8_t*)malloc(result.capacity);
    fseek(file, 0, SEEK_SET);

    fread(result.items, result.capacity, 1, file);
    fclose(file);

    return result;
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

static void disassemble_bytecode(const char* bytecode_file)
{

    Vl_ByteArray bytecode = read_all_file(bytecode_file);
    if (bytecode.items == NULL) {
        fprintf(stderr, "ERROR: failed to read file %s: %s\n", bytecode_file, strerror(errno));
        exit(1);
    }
    fprintf(stderr, "INFO: disassembling bytecode '%s'\n", bytecode_file);
    vl_disassemble_bytecode(stdout, bytecode);
    vl_list_free(&bytecode);
}

static void run_bytecode(const char* bytecode_file)
{
    fprintf(stderr, "INFO: running bytecode '%s'\n", bytecode_file);
    // TODO: come up with a magic header to distinguish bytecode
    // format from other binary files and check it when
    // reading the file.
    Vl_ByteArray bytecode = read_all_file(bytecode_file);
    if (bytecode.items == NULL) {
        fprintf(stderr, "ERROR: failed to read file %s: %s\n", bytecode_file, strerror(errno));
        exit(1);
    }

    Vl_Vm vm = { 0 };

    vl_vm_load_bytecode(&vm, bytecode.items, bytecode.length);
    if (!vl_vm_execute(&vm)) {
        exit(1);
    }
    vl_list_free(&bytecode);
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

    } else if (strcmp(subcommand, "disasm") == 0) {
        if (!argc) {
            usage(program);
            fprintf(stderr, "ERROR: no file was provided\n");
            return 1;
        }
        const char* bytecode_file = shift_args(&argc, &argv);
        disassemble_bytecode(bytecode_file);

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
