#include <stdio.h>

#include "lexer.h"
#include "list.h"

bool read_all_file(const char* path, char** data, size_t* data_size)
{
    FILE* file = fopen(path, "rb");

    if (file == NULL) {
        return false;
    }

    fseek(file, 0, SEEK_END);
    *data_size = ftell(file);
    *data = (char*)malloc(*data_size);
    fseek(file, 0, SEEK_SET);

    fread(*data, *data_size, 1, file);
    fclose(file);

    return true;
}

int main()
{
    const char* path = "./test.vl";

    char* src = NULL;
    size_t src_size = 0;

    if (!read_all_file(path, &src, &src_size)) {
        fprintf(stderr, "failed to read file: %s\n", path);
        return 1;
    }

    vl_lexer_t lexer = { 0 };
    vl_lex_init(&lexer, path, src, src_size);

    if (!vl_lex_scan_all(&lexer)) {
        vl_lex_free(&lexer);
        fprintf(stderr, "lexer failed\n");
        return 1;
    }

    for (int i = 0; i < lexer.tokens.length - 1; i++) {
        printf("%.*s\n", (int)lexer.tokens.items[i].lexeme_length, lexer.tokens.items[i].lexeme);
    }

    vl_lex_free(&lexer);
}