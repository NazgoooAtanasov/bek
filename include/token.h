#ifndef BEK_TOKEN_
#define BEK_TOKEN_

#include <stdlib.h>

enum TokenType {
    NUM,
    INST
};

enum TokenInst {
    PUSH,
    PLUS,
    MINUS,
    RET
};

struct _Token {
    int type;
    int data;
    int line;
};
typedef struct _Token Token;

void token_create(Token* tk, int type, int data, int line);
/* void token_destroy(Token* tk); */

#endif // BEK_TOKEN_
