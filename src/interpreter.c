#include "../include/interpreter.h"

void interpreter_create(Interpreter* intr, uint8_t* bin_buff) {
    intr->bin_buff = bin_buff;
    intr->bin_ptr = 0;
    intr->running = 0;
    intr->status = I_NOT_STARTED;
    intr->exit = 69696969;
    intr->stack_ptr = 0;
}

int interpreter_run(Interpreter* intr) {
    intr->running = 1;

    while(intr->running) {
        switch(intr->bin_buff[intr->bin_ptr++]) {
            case PUSH_OP: {
                printf("Detected PUSH_OP\n");
                break;
            }

            case PLUS_OP: {
                printf("Detected ADD_OP\n");
                break;
            }

            case RET_OP: {
                printf("Detected RET_OP\n");

                intr->running = 0;
                break;
            }
        }
    }

    for (int i = 0; i < intr->stack_ptr; i++) {
        printf("%d\n", intr->stack[i]);
    }

    intr->status = I_FINISHED;

    return intr->status;
}

uint32_t read32(uint8_t* buffer, size_t idx) {
    return (buffer[idx] << 24) | (buffer[idx + 1] << 16) |
        (buffer[idx + 2] << 8) | (buffer[idx + 3]);
}

void push8(Interpreter* intr, uint8_t data) {
    intr->stack[++intr->stack_ptr] = data;
}

void push16(Interpreter* intr, uint16_t data) {
    push8(intr, (data & 0xFF00) >> 8);
    push8(intr, (data & 0x00FF));
}

void push32(Interpreter* intr, uint32_t data) {
    push16(intr, (data & 0xFFFF0000) >> 16);
    push16(intr, (data & 0x0000FFFF));
}

uint8_t pop8(Interpreter* intr) {
    return intr->stack[intr->stack_ptr--];
}

uint16_t pop16(Interpreter* intr) {
    uint16_t b = pop8(intr);
    uint16_t a = pop8(intr);

    return (a << 8) | b;
}

uint32_t pop32(Interpreter* intr) {
    uint16_t b = pop16(intr);
    uint16_t a = pop16(intr);

    return (a << 16) | b;
}