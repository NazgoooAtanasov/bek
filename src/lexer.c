#include "../include/lexer.h"

void lexer_create(Lexer* lex) {
    assert(TOKEN_TYPE_COUNT == 2);
    assert(TOKEN_INST_COUNT == 6);

    lex->inst_count = 0;
    lex->size = 1024 * 8;
    lex->tokens = (Token*) malloc(sizeof(Token) * lex->size);
}

void lexer_parse(Lexer* lex, const char* file_buff) {
    char word[256];
    int word_i = 0;
    int i = 0;
    int line = 1;

    while(1) {
        while(file_buff[i] != ' ' && file_buff[i] != '\n' && file_buff[i] != '\0') {
            word[word_i++] = file_buff[i++];
        }
        word[word_i] = '\0';

        Token token;

        // handling empty strings.
        if (strcmp(word, "") != 0) {
            if (word[0] == '#') {
                int parsed_number = lexer_parse_int(word);

                token_create(&token, NUM, parsed_number, line);
                lexer_add_token(lex, &token);
            }

            else {
                if (strcmp(word, "push") == 0) {
                    token_create(&token, INST, PUSH, line);
                    lexer_add_token(lex, &token);
                }
                else if (strcmp(word, "+") == 0) {
                    token_create(&token, INST, PLUS, line);
                    lexer_add_token(lex, &token);
                }
                else if (strcmp(word, "-") == 0) {
                    token_create(&token, INST, MINUS, line);
                    lexer_add_token(lex, &token);
                }
                else if (strcmp(word, "*") == 0) {
                    token_create(&token, INST, MULT, line);
                    lexer_add_token(lex, &token);
                }
                else if (strcmp(word, "/") == 0) {
                    token_create(&token, INST, DEV, line);
                    lexer_add_token(lex, &token);
                }
                else if (strcmp(word, "ret") == 0) {
                    token_create(&token, INST, RET, line);
                    lexer_add_token(lex, &token);
                }
                else {
                    fprintf(stderr, "No such instruction, reading '%s'\n", word);
                }
            }
        }

        if (file_buff[i] == '\n') line++;
        else if (file_buff[i] == '\0') break;

        memset(word, 0, sizeof(word));
        word_i = 0;
        i++;
    }
}

void lexer_add_token(Lexer* lex, Token* tk) {
    if (lex->inst_count >= lex->size) {
        lex->size *= 2;
        lex->tokens = (Token*) realloc(lex->tokens, sizeof(Token) * lex->size);
    }
    
    lex->tokens[lex->inst_count++] = *tk;
}

uint32_t lexer_parse_int(const char* buf) {
	long num = atoi(&buf[1]);
	return (num <= UINT32_MAX) ? num : 0;
}

void lexer_destroy(Lexer* lex) {
    free(lex->tokens);
}
