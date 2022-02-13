#ifndef BEK_LEXER_
#define BEK_LEXER_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "token.h"

struct _Lexer {
    Token* tokens;
    int inst_count;
    size_t size;
};
typedef struct _Lexer Lexer;

void lexer_create(Lexer* lex);

void lexer_parse(Lexer* lex, const char* file_buff);

uint32_t lexer_parse_int(const char* buf);

void lexer_add_token(Lexer* lex, Token* tk);

void lexer_destroy(Lexer* lex);

#endif // BEK_LEXER_
