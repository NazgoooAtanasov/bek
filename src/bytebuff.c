#include "../include/bytebuff.h"

void bytebuff_create(ByteBuff* bf) {
    bf->ptr = 0;
    bf->buff_sz = 1024;
    bf->buffer = (uint8_t*) malloc(sizeof(uint8_t) * bf->buff_sz);
}

void add_byte8(ByteBuff* bf, uint8_t data) {
    if (bf->ptr >= bf->buff_sz) {
        bf->buff_sz *= 2;
        bf->buffer = (uint8_t*) realloc(bf->buffer, sizeof(uint8_t) * bf->buff_sz);
    }

    bf->buffer[bf->ptr++] = data;
}

void add_byte16(ByteBuff* bf, uint16_t data) {
    add_byte8(bf, (data & 0xFF00) >> 8);
    add_byte8(bf, (data & 0x00FF));
}

void add_byte32(ByteBuff* bf, uint32_t data) {
    add_byte16(bf, (data & 0xFFFF0000) >> 16);
    add_byte16(bf, (data & 0x0000FFFF));
}

void bytebuff_destroy(ByteBuff* bf) {
    free(bf->buffer);
}
