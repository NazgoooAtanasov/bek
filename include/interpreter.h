#ifndef BEK_INTERPRETER_
#define BEK_INTERPRETER_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "bytebuff.h"
#include "opcodes.h"

#define STACK_CAP 1024

enum _IntrStatus {
    I_NOT_STARTED,
    I_FINISHED,
    I_ERROR
};

struct _Interpreter {
    uint8_t* bin_buff;
    size_t bin_ptr;

    uint8_t stack[STACK_CAP];
    size_t stack_ptr;

    int running;
    int status;

    int exit;
};

typedef struct _Interpreter Interpreter;

void interpreter_create(Interpreter* intr, uint8_t* bin_buff);
int interpreter_run(Interpreter* intr);
/* void interpreter_destroy(Interpreter* intr); */

void push8(Interpreter* intr, uint8_t data);
void push16(Interpreter* intr, uint16_t data);
void push32(Interpreter* intr, uint32_t data);

uint8_t pop8(Interpreter* intr);
uint16_t pop16(Interpreter* intr);
uint32_t pop32(Interpreter* intr);

uint32_t read32(uint8_t* buffer, size_t idx);
#endif // BEK_INTERPRETER_
