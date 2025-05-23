#ifndef VL_LEXER_H_
#define VL_LEXER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    vl_tokentype_none = 0,
} vl_tokentype_t;

typedef struct {
    vl_tokentype_t type;
    int32_t line;
    int32_t column;
} vl_token_t;

typedef struct {
    vl_token_t* items;
    size_t capacity;
    size_t length;
} vl_tokenlist_t;

typedef struct {

} vl_lexer_t;

#endif // VL_LEXER_H_
