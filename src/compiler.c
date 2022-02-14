#include "../include/compiler.h"

void compiler_create(Compiler* comp, const char* output_file) {
    assert(OP_CODES_COUNT == 4);

    comp->running = 0;
    comp->status = C_NOT_STARTED;
    comp->output_file = output_file;
}

int compiler_compile(Compiler* comp, Token* tokens, int tokens_count) {
    comp->running = 1;

    ByteBuff bf;
    bytebuff_create(&bf);

    for (int i = 0; i < tokens_count; i++) {
        if (tokens[i].type == NUM) {
            add_byte32(&bf, tokens[i].data);
        }
        else {
            switch (tokens[i].data) {
                case PUSH: {
                    add_byte8(&bf, PUSH_OP);
                    break;
                }

                case PLUS: {
                    add_byte8(&bf, PLUS_OP);
                    break;
                }

                case MINUS: {
                    add_byte8(&bf, MINUS_OP);
                    break;
                }
                
                case RET: {
                    add_byte8(&bf, RET_OP);
                    break;
                }
            }
        }
    }

    write_binary(&bf, comp->output_file);
    bytebuff_destroy(&bf);

    // Use the status of the compiler properly
    comp->status = C_FINISHED;
    return comp->status;
}
