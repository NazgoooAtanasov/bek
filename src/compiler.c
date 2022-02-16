#include "../include/compiler.h"

void compiler_create(Compiler* comp, const char* output_file) {
    assert(OP_CODES_COUNT == 7);

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
            uint32_t data = *((uint32_t*) tokens[i].data);
            add_byte32(&bf, data);
        }
        else {
            int instruction = *((int*) tokens[i].data);
            switch (instruction) {
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

                case MULT: {
                    add_byte8(&bf, MULT_OP);
                    break;
                }

                case DEV: {
                    add_byte8(&bf, DEV_OP);
                    break;
                }

                case PRINT: {
                    add_byte8(&bf, PRINT_OP);
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
