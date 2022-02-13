#include <stdio.h>
#include <string.h>

#include "../include/util.h"
#include "../include/lexer.h"

int main(int argc, char* argv[]) {
    if(argc >= 3) {
        char* command = argv[1];
        char* filepath = argv[2];

        if (strcmp(command, "comp") == 0) {
            Lexer lex;
            char* file_buff = read_file(filepath);

            lexer_create(&lex);
            lexer_parse(&lex, file_buff);

            for (int i = 0; i < lex.inst_count; i++) {
                printf("%d, %d, %d\n", 
                    lex.tokens[i].type,
                    lex.tokens[i].data,
                    lex.tokens[i].line
                );
            }

            lexer_destroy(&lex);

            free(file_buff);
        }

        return 0;
    }

    fprintf(stderr, "Not enough arguments\n");
    return 1;
}
