#include "lexer.h"
#include <stdio.h>
#include <vl/common/vl_list.h>

void vl_lex_init(vl_lexer_t* l, const char* source_file, const char* source, size_t source_length)
{
    l->source = source;
    l->source_length = source_length;
    l->start = 0;
    l->current = 0;
    l->column = 0;
    l->line = 1;
    l->tokens = (vl_tokenlist_t) { 0 };

    l->source_file = source_file;
}

void vl_lex_free(vl_lexer_t* l)
{
    vl_list_free(&l->tokens);
}

char vl_lex_advance(vl_lexer_t* l)
{
    if (!vl_lex_is_end(l)) {
        char c = l->source[l->current];
        l->current++;
        l->column++;
        return c;
    }

    return '\0';
}

bool vl_lex_is_end(vl_lexer_t* l)
{
    return (size_t)l->current >= l->source_length;
}

char vl_lex_peek(vl_lexer_t* l)
{
    if (!vl_lex_is_end(l)) {
        return l->source[l->current];
    }
    return '\0';
}

char vl_lex_peek_next(vl_lexer_t* l)
{
    if ((size_t)l->current + 1 >= l->source_length) {
        return '\0';
    }

    return l->source[l->current + 1];
}

void vl_lex_add_token(vl_lexer_t* l, vl_tokentype_t type)
{
    vl_token_t token = { 0 };

    token.type = type;
    token.lexeme = &l->source[l->start];
    token.lexeme_length = l->current - l->start;

    vl_list_append(&l->tokens, token);
}

bool vl_lex_scan_token(vl_lexer_t* l)
{
    char c = vl_lex_advance(l);

    switch (c) {
    case '+':
        vl_lex_add_token(l, VL_TOKEN_PLUS);
        break;
    case '-':
        vl_lex_add_token(l, VL_TOKEN_PLUS);
        break;
    case '*':
        vl_lex_add_token(l, VL_TOKEN_STAR);
        break;
    case '(':
        vl_lex_add_token(l, VL_TOKEN_LEFTPAREN);
        break;
    case ')':
        vl_lex_add_token(l, VL_TOKEN_RIGHTPAREN);
        break;

    case '/':
        if (vl_lex_match(l, '/')) {
            while (!vl_lex_is_end(l) && vl_lex_peek(l) != '\n') {
                vl_lex_advance(l);
            }
        } else {
            vl_lex_add_token(l, VL_TOKEN_SLASH);
        }
        break;

    case ' ':
    case '\r':
    case '\t':
        break;

    case '\n':
        l->line++;
        l->column = 0;
        break;

    default:
        if (vl_is_digit(c)) {
            bool success = vl_lex_scan_number(l);
            if (!success) {
                return false;
            }
        } else {
            fprintf(stderr, "%s:%d:%d: illegal character: %c\n", l->source_file, l->line, l->column, c);
            return false;
        }
        break;
    }

    return true;
}

bool vl_lex_scan_all(vl_lexer_t* l)
{
    bool success = true;
    while (!vl_lex_is_end(l)) {
        l->start = l->current;
        success = success && vl_lex_scan_token(l);
    }

    vl_lex_add_token(l, VL_TOKEN_EOF);
    return success;
}

bool vl_lex_scan_number(vl_lexer_t* l)
{
    while (vl_is_digit(vl_lex_peek(l))) {
        vl_lex_advance(l);
    }

    vl_lex_add_token(l, VL_TOKEN_NUMBER);
    return true;
}

bool vl_lex_match(vl_lexer_t* l, char c)
{

    if (vl_lex_peek(l) == c) {
        l->current++;
        return true;
    }

    return false;
}

void vl_lex_err(vl_lexer_t* l, const char* errmsg)
{
    (void)l;
    (void)errmsg;
}

bool vl_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

bool vl_is_alpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}

bool vl_is_alphanumeric(char c)
{
    return vl_is_digit(c) || vl_is_alpha(c);
}
