#include "../include/lexer.h"

void lexer_create(Lexer* lex) {
    assert(TOKEN_TYPE_COUNT == 3);
    assert(TOKEN_INST_COUNT == 15);

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
        int condition = file_buff[i] != ' ' && file_buff[i] != '\n' && file_buff[i] != '\0' ? 1 : 0;
        int quote = 0;
        while(condition) {
            int inner_condition;
            word[word_i++] = file_buff[i++];

            // if " start -> stop space parse
            // if " end -> start space parse
            
            if (word[word_i - 1] == '"' && quote == 0) {
                quote = 1;
                inner_condition = file_buff[i] != '\n' && file_buff[i] != '\0' ? 1 : 0;
            } else if (word[word_i - 1] == '"' && quote == 1) {
                quote = 0;
                inner_condition = file_buff[i] != ' ' && file_buff[i] != '\n' && file_buff[i] != '\0' ? 1 : 0;
            } else if (quote == 1) {
                inner_condition = file_buff[i] != '\n' && file_buff[i] != '\0' ? 1 : 0;
            } else {
                inner_condition = file_buff[i] != ' ' && file_buff[i] != '\n' && file_buff[i] != '\0' ? 1 : 0;
            }

            condition = inner_condition;
        }
        word[word_i] = '\0';

        Token token;

        // handling empty strings.
        if (strcmp(word, "") != 0) {
            if (word[0] == '#') {
                uint32_t* parsed_number = (uint32_t*) malloc(sizeof(uint32_t));
                *parsed_number = lexer_parse_int(word);

                token_create(&token, NUM, parsed_number, line);
                lexer_add_token(lex, &token);
            }

            // add the logic to take all of the stuff between the ""
            else if (word[0] == '~') {
                uint8_t* string = (uint8_t*) malloc(sizeof(uint8_t) * 256);
                memset(string, '\0', 256);

                lexer_parse_string(string, &word[2]);

                token_create(&token, STR, string, line);
                lexer_add_token(lex, &token);
            }

            else {
                int* inst = (int*) malloc(sizeof(int));

                if (strcmp(word, "push") == 0) {
                    *inst = PUSH;
                }
                else if (strcmp(word, "+") == 0) {
                    *inst = PLUS;
                }
                else if (strcmp(word, "-") == 0) {
                    *inst = MINUS;
                }
                else if (strcmp(word, "*") == 0) {
                    *inst = MULT;
                }
                else if (strcmp(word, "/") == 0) {
                    *inst = DEV;
                }
                else if (strcmp(word, "print") == 0) {
                    *inst = PRINT;
                }
                else if (strcmp(word, "ret") == 0) {
                    *inst = RET;
                }
                else if (strcmp(word, "!") == 0) {
                    *inst = CONDITION;
                }
                else if (strcmp(word, "if") == 0) {
                    *inst = CONDITION_START;
                }
                else if (strcmp(word, "end") == 0) {
                    *inst = END_BLOCK;
                }
                else if (strcmp(word, "==") == 0) {
                    *inst = CONDITION_EQ;
                }
                else if (strcmp(word, ">=") == 0) {
                    *inst = CONDITION_BIGGER_EQ;
                }
                else if (strcmp(word, "<=") == 0) {
                    *inst = CONDITION_LESS_EQ;
                }
                else if (strcmp(word, ">") == 0) {
                    *inst = CONDITION_BIGGER;
                }
                else if (strcmp(word, "<") == 0) {
                    *inst = CONDITION_LESS;
                }
                else {
                    fprintf(stderr, "No such instruction, reading '%s'\n", word);
                }

                token_create(&token, INST, inst, line);
                lexer_add_token(lex, &token);
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

void lexer_parse_string(uint8_t* buff, const char* str) {
    uint8_t len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '"') {
            buff[i] = '\0';
            break;
        }

        buff[i] = str[i];
    }
}

void lexer_destroy(Lexer* lex) {
    for (int i = 0; i < lex->inst_count; i++) {
        free(lex->tokens[i].data);
    }

    free(lex->tokens);
}
