#include "../include/interpreter.h"

void interpreter_create(Interpreter* intr, uint8_t* bin_buff) {
    intr->bin_buff = bin_buff;
    intr->bin_ptr = 0;
    intr->running = 0;
    intr->status = I_NOT_STARTED;
    intr->exit = 69696969;
    intr->stack_ptr = 0;
    intr->stack_sz = 0;
    intr->type_stack_ptr = 0;
    intr->type_stack_sz = 0;
}

int interpreter_run(Interpreter* intr) {
    intr->running = 1;

    while(intr->running) {
        switch(intr->bin_buff[intr->bin_ptr++]) {
            case PUSH_OP: {
                uint8_t type = read8(intr->bin_buff, intr->bin_ptr++);

                if (type == TYPE_NUMBER) {
                    uint32_t val = read32(intr->bin_buff, intr->bin_ptr);

                    push32(intr->stack, &intr->stack_ptr, val);

                    intr->bin_ptr += 4;
                    intr->stack_sz++;

                    push8(intr->type_stack, &intr->type_stack_ptr, TYPE_NUMBER);
                }

                else if (type == TYPE_STRING) {
                    char str[256];
                    size_t str_i = 0;
                    char s = read8(intr->bin_buff, intr->bin_ptr++);
                    push8(intr->stack, &intr->stack_ptr, s);

                    while (1) {
                        str[str_i++] = s;

                        if (s == '\0') break;

                        s = read8(intr->bin_buff, intr->bin_ptr++);
                        push8(intr->stack, &intr->stack_ptr, s);
                    }

                    intr->stack_sz++;

                    push8(intr->type_stack, &intr->type_stack_ptr, TYPE_STRING);
                    intr->type_stack_sz++;
                }

                break;
            }

            case PLUS_OP: {
                uint32_t a = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                uint32_t b = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                push32(intr->stack, &intr->stack_ptr, a + b);
                intr->stack_sz++;
                break;
            }

            case MINUS_OP: {
                uint32_t a = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                uint32_t b = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                push32(intr->stack, &intr->stack_ptr, b - a);
                intr->stack_sz++;
                break;
            }

            case MULT_OP: {
                uint32_t a = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                uint32_t b = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                push32(intr->stack, &intr->stack_ptr, a * b);
                intr->stack_sz++;
                break;
            }

            case DEV_OP: {
                uint32_t a = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                uint32_t b = pop32(intr->stack, &intr->stack_ptr);
                intr->stack_sz--;

                push32(intr->stack, &intr->stack_ptr, b / a);
                intr->stack_sz++;
                break;
            }

            case PRINT_OP: {
                uint8_t type = pop8(intr->type_stack, &intr->type_stack_ptr);
                intr->type_stack_sz--;

                if (type == TYPE_NUMBER) {
                    uint32_t a = pop32(intr->stack, &intr->stack_ptr);
                    intr->stack_sz--;

                    fprintf(stdout, "%d\n", a);
                }

                else if (type == TYPE_STRING) {
                    char str[256];
                    size_t str_i = 0;
                    char s = pop8(intr->stack, &intr->stack_ptr);
                    intr->stack_sz--;

                    while (1) {
                        if (s == '\0' && str_i != 0) break;

                        if (s != '\0')
                            str[str_i++] = s;

                        s = pop8(intr->stack, &intr->stack_ptr);
                        intr->stack_sz--;
                    }
                    fprintf(stdout, "%s\n", strrev(str));
                }

                break;
            }

            case RET_OP: {
                intr->exit = intr->stack_sz ? pop32(intr->stack, &intr->stack_ptr) : 0;
                intr->running = 0;
                break;
            }

            default: {
                fprintf(stderr, "Inrecognized operation\n");
            }
        }
    }

    intr->status = I_FINISHED;

    return intr->status;
}

uint32_t read32(uint8_t* buffer, size_t idx) {
    return (buffer[idx] << 24) | (buffer[idx + 1] << 16) |
        (buffer[idx + 2] << 8) | (buffer[idx + 3]);
}

uint8_t read8(uint8_t* buffer, size_t idx) {
    return buffer[idx];
}

void push8(uint8_t* stack, size_t* stack_ptr, uint8_t data) {
    stack[++(*stack_ptr)] = data;
}

void push16(uint8_t* stack, size_t* stack_ptr, uint16_t data) {
    push8(stack, stack_ptr, (data & 0xFF00) >> 8);
    push8(stack, stack_ptr, (data & 0x00FF));
}

void push32(uint8_t* stack, size_t* stack_ptr, uint32_t data) {
    push16(stack, stack_ptr, (data & 0xFFFF0000) >> 16);
    push16(stack, stack_ptr, (data & 0x0000FFFF));
}

uint8_t pop8(uint8_t* stack, size_t* stack_ptr) {
    return stack[(*stack_ptr)--];
}

uint16_t pop16(uint8_t* stack, size_t* stack_ptr) {
    uint16_t b = pop8(stack, stack_ptr);
    uint16_t a = pop8(stack, stack_ptr);

    return (a << 8) | b;
}

uint32_t pop32(uint8_t* stack, size_t* stack_ptr) {
    uint16_t b = pop16(stack, stack_ptr);
    uint16_t a = pop16(stack, stack_ptr);

    return (a << 16) | b;
}
