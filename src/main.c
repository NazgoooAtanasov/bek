#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../include/util.h"
#include "../include/lexer.h"
#include "../include/compiler.h"
#include "../include/interpreter.h"
#include "../include/opcodes.h"

int main(int argc, char* argv[]) {
    if(argc >= 3) {
        char* command = argv[1];
        char* filepath = argv[2];

        if (strcmp(command, "comp") == 0) {
            Lexer lex;
            Compiler comp;
            char* file_buff = read_file(filepath);

            lexer_create(&lex);
            lexer_parse(&lex, file_buff);

            /* for (int i = 0; i < lex.inst_count; i++) { */
            /*     if (lex.tokens[i].type == STR) */
            /*         printf("%s\n", (char*) lex.tokens[i].data); */
            /*     else */
            /*         printf("%d\n", *((int*) lex.tokens[i].data)); */
            /* } */

            compiler_create(&comp, argc >= 4 ? argv[3] : "out.bin");
            int status = compiler_compile(&comp, lex.tokens, lex.inst_count);

            lexer_destroy(&lex);
            free(file_buff);
        }
        else if (strcmp(command, "exec") == 0) {
            Interpreter interpreter;

            uint8_t* binary_file_buffer = read_file_binary(filepath);

            interpreter_create(&interpreter, binary_file_buffer);
            int status = interpreter_run(&interpreter);

            return interpreter.exit;
        }

        return 0;
    }

    fprintf(stderr, "Not enough arguments\n");
    return 1;
}
