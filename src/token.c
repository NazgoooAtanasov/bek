#include "../include/token.h"

void token_create(Token* tk, int type, int data, int line) {
    tk->type = type;
    tk->data = data;
    tk->line = line;
}
