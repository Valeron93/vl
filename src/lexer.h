#ifndef VL_LEXER_H_
#define VL_LEXER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    VL_TOKEN_NONE = 0,

    VL_TOKEN_PLUS,
    VL_TOKEN_MINUS,
    VL_TOKEN_STAR,
    VL_TOKEN_SLASH,

    VL_TOKEN_LEFTPAREN,
    VL_TOKEN_RIGHTPAREN,

    VL_TOKEN_NUMBER,

    VL_TOKEN_EOF,
    VL_TOKEN_COUNT,

} vl_tokentype_t;

typedef struct {
    vl_tokentype_t type;
    int32_t line;
    int32_t column;

    const char* lexeme;
    size_t lexeme_length;

    union {
        double double_value;
        struct {
            const char* str;
            size_t len;
        } string_value;
    };
} vl_token_t;

typedef struct {
    vl_token_t* items;
    size_t capacity;
    size_t length;
} vl_tokenlist_t;

typedef struct {
    const char* source;
    size_t source_length;

    const char* source_file;

    vl_tokenlist_t tokens;

    int32_t start;
    int32_t current;
    int32_t line;
    int32_t column;
} vl_lexer_t;

void vl_lex_init(vl_lexer_t* l, const char* source_file, const char* source, size_t source_length);
void vl_lex_free(vl_lexer_t* l);

char vl_lex_advance(vl_lexer_t* l);
bool vl_lex_is_end(vl_lexer_t* l);
char vl_lex_peek(vl_lexer_t* l);
char vl_lex_peek_next(vl_lexer_t* l);

void vl_lex_add_token(vl_lexer_t* l, vl_tokentype_t type);

bool vl_lex_scan_token(vl_lexer_t* l);
bool vl_lex_scan_all(vl_lexer_t* l);
bool vl_lex_scan_number(vl_lexer_t* l);

bool vl_lex_match(vl_lexer_t* l, char c);

void vl_lex_err(vl_lexer_t* l, const char* errmsg);

bool vl_is_digit(char c);
bool vl_is_alpha(char c);
bool vl_is_alphanumeric(char c);

#endif // VL_LEXER_H_
