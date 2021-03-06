#ifndef BEK_TOKEN_
#define BEK_TOKEN_

#include <stdlib.h>

enum TokenType {
    NUM,
    INST,
    STR,

    TOKEN_TYPE_COUNT
};

enum TokenInst {
    PUSH,
    PLUS,
    MINUS,
    MULT,
    DEV,
    RET,
    PRINT,

    END_BLOCK,

    CONDITION,
    CONDITION_START,

    CONDITION_EQ,
    CONDITION_BIGGER_EQ,
    CONDITION_LESS_EQ,
    CONDITION_BIGGER,
    CONDITION_LESS,

    TOKEN_INST_COUNT
};

struct _Token {
    int type;
    void* data;
    int line;
};
typedef struct _Token Token;

void token_create(Token* tk, int type, void* data, int line);
/* void token_destroy(Token* tk); */

#endif // BEK_TOKEN_
